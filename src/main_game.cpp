#include <algorithm>
#include <GL/glew.h>
#include <iostream>
#include <jaogll/jaogll.h>
#include <jaogll/resource_manager.h>

#include "../inc/main_game.h"
#include "../inc/human.h"

float Bullet::maxLiveTime = 100;

const JOGL::Color white ( 255, 255, 255, 255 );

GameState MainGame::_gameState = GameState::PLAY;

MainGame::MainGame ( unsigned w_width, unsigned w_height )
    : _w_width ( w_width )
      , _w_height ( w_height )
      , MAX_FPS ( 144 )
      ,  _player_start ( 200, 200 )
      , _player ( new Player )
{
    JOGL::init();

    _window.create( "Zombie 0.1", _w_width, _w_height, 0 );

    _window.set_clear_color( JOGL::Color ( 200, 200, 200, 255 ) );

    initShaders();

    _camera.init( w_width, w_height );

    _spriteBatch.init();

    _fpsLimiter.init( MAX_FPS );

    _level.init( "../resources/level_file.dat", 50 );
    _level.add_character_image( 'W', "../media/bricksx64.png" );
    _level.add_character_image( '.', "../media/Green_3_gridbox.png" );
    _level.generate_level();

    init_agents();

    _camera.setPosition( _player_start );

    // init collision manager
    auto v = _level.getSprites();
    JOGL::GLTexture floor = JOGL::ResourceManager::getTexture( "../media/Green_3_gridbox.png" );
    _collision.set_level(
            std::vector<JOGL::Sprite> (
                    v.begin()
                    , std::remove_if( v.begin(), v.end(), [floor]( JOGL::Sprite A ){
                        return A.texture.id == floor.id;
                    } )
            )
    );

    _agent_manager.init( _player );
    Bullet bullet_sample;
    bullet_sample.init( 10, JOGL::Sprite( 0, 0, 5, 5, white, "../media/PNG/Coin.png", 0 ), 3, AgentType::BULLET );
    _agent_manager.add_bullet_sample( bullet_sample );
}

void MainGame::init_agents ()
{
    _player->init( 3
            , JOGL::Sprite ( _player_start.x, _player_start.y, 40, 40, white
                    , "../media/PNG/CharacterRight_Standing.png", 0 )
            , 20
            , AgentType::PLAYER );

    _zombies.push_back( new Zombie );
    _zombies.back()->init( 1
            , JOGL::Sprite ( _player_start.x + 100, _player_start.y + 100, 40, 40, white
                    , "../media/PNG/CharacterLeft_Standing.png", 0 )
            , 20
            , AgentType::ZOMBIE );
    _agent_manager.add_agent( dynamic_cast<Agent*>(_zombies.back()) );

    std::vector<Human*> humans;

    // set up humans
    for ( int i = 0; i < 2; ++i )
    {
        humans.emplace_back( new Human );
        humans.back()->init( 1
                , JOGL::Sprite ( 500 + 50 * i, 200, 40, 40, white
                        , "../media/PNG/CharacterRight_Standing.png", 0 )
                , 20
                , AgentType::HUMAN );
        _agent_manager.add_agent( dynamic_cast<Human*>(humans.back()) );
    }
}

void MainGame::initShaders ()
{
    _colorProgram = new JOGL::GLSLCompiler;
    _colorProgram->compileShaders( "../shaders/colorShading.vert", "../shaders/colorShading.frag" );
    _colorProgram->addAttribute( "vertexPosition" );
    _colorProgram->addAttribute( "vertexColor" );
    _colorProgram->addAttribute( "vertexUV" );
    _colorProgram->linkShaders();
}

void MainGame::run ()
{
    game_loop();
}

void MainGame::game_loop ()
{
    while ( _gameState != GameState::QUIT )
    {
        process_input();

        _agent_manager.ai();

        _camera.update();

        collide();

        _agent_manager.update();

        drawGame();
        _fpsLimiter.limit();
    }

    for ( GLenum err; (err = glGetError()) != GL_NO_ERROR; )
    {
        fprintf( stderr, "ERROR: OpenGL error %d.\n", err );
    }

}

void MainGame::collide ()
{
    _collision.set_agents( _agent_manager.get_agents() );
    for ( auto&& agent : _agent_manager.get_agents() )
    {
        Agent* a = _collision.collide( agent );
        if ( a != nullptr )
        {
            _agent_manager.agent_collided( agent, a );
            _agent_manager.agent_collided( a, agent );
        }
    }
}

int MainGame::process_input ()
{
    SDL_Event event;

    const float CAMERA_SPEED = 1.0f;
    const float SCALE_SPEED = .01f;
    static bool shot = false;

    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:
                MainGame::set_gameState( GameState::QUIT );
                break;
            case SDL_KEYDOWN:
                _inputManager.press_key( event.key.keysym.sym );
                break;
            case SDL_KEYUP:
                _inputManager.release_key( event.key.keysym.sym );
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.press_key( event.button.button );
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.release_key( event.button.button );
                break;
            case SDL_MOUSEMOTION:
                _inputManager.set_mouse_coords( event.motion.x, event.motion.y );
                break;
            default:
                break;
        }
    }

    std::map<unsigned int,glm::vec2> dirs {
            { SDLK_w, glm::vec2( 0, 1 ) },
            { SDLK_s, glm::vec2( 0, -1 ) },
            { SDLK_a, glm::vec2( -1, 0 ) },
            { SDLK_d, glm::vec2( 1, 0 ) }
    };

    _player->set_vel_unit( glm::vec2 ( 0, 0 ) );

    for ( auto&& dir : dirs )
    {
        if ( _inputManager.is_key_presses( dir.first ) )
        {
            if ( ! ( glm::dot( _player->get_vel_unit(), dir.second ) > 0 ) )
            {
                if ( _player->get_vel_unit() + dir.second == glm::vec2 ( 0, 0 ) )
                {
                    _player->set_vel_unit( glm::vec2 ( 0, 0 ) );
                }
                else
                {
                    _player->set_vel_unit( glm::normalize( _player->get_vel_unit() + dir.second ) );
                }
            }
        }
    }

    if ( _inputManager.is_key_presses( SDLK_q ) )
    {
        _camera.setScale( _camera.getScale() + SCALE_SPEED );
    }
    if ( _inputManager.is_key_presses( SDLK_e ) )
    {
        _camera.setScale( _camera.getScale() - SCALE_SPEED );
    }
    if ( ! shot && _inputManager.is_key_presses( SDL_BUTTON_LEFT ) )
    {
        glm::vec2 mouseCoords = _inputManager.get_mouse_coords();
        mouseCoords = _camera.convert_screen_to_world( mouseCoords );
        _agent_manager.player_shoot( mouseCoords );
        shot = true;
    }
    if ( ! _inputManager.is_key_presses( SDL_BUTTON_LEFT ) )
    {
        shot = false;
    }

    //printf( "%lf : %lf\n", _player->get_vel_unit().x, _player->get_vel_unit().y );

    _camera.setPosition( _player->get_pos() );

    return 0;
}

void MainGame::drawGame ()
{
    _colorProgram->use();

    // set texture
    glActiveTexture( GL_TEXTURE0 );
    GLint textureLocation = _colorProgram->get_uniformLocation( "mySampler" );
    glUniform1i( textureLocation, 0 );

    // set camera matrix
    GLint pLocation = _colorProgram->get_uniformLocation( "P" );
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv( pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]) );

    _spriteBatch.begin();

    for ( auto&& sprite : _level.getSprites() )
    {
        _spriteBatch.add_sprite( sprite );
    }

    for ( auto&& agent : _agent_manager.get_agents() )
    {
        _spriteBatch.add_sprite( agent->get_sprite() );
    }

    _spriteBatch.end();

    _spriteBatch.render_batch();

    _colorProgram->unuse();

    _window.swap();
}

MainGame::~MainGame ()
{
    SDL_Quit();
}

void MainGame::set_gameState ( GameState _gameState )
{
    MainGame::_gameState = _gameState;
}
