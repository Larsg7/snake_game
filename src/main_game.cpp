#include <algorithm>
#include <GL/glew.h>
#include <iostream>
#include <jaogll/jaogll.h>
#include <jaogll/resource_manager.h>

#include "../inc/main_game.h"

float Bullet::maxLiveTime = 100;

const JOGL::Color white ( 255, 255, 255, 255 );

MainGame::MainGame ( unsigned w_width, unsigned w_height )
    : _w_width ( w_width )
      , _w_height ( w_height )
      , MAX_FPS ( 60 )
      , _gameState ( GameState::PLAY )
      ,  _player_start ( 200, 200 )
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

    std::vector<Agent*> a;
    a.emplace_back( &_player );
    _collision.set_agents( a );
}

void MainGame::init_agents ()
{
    Bullet bullet_sample;
    bullet_sample.init( 20, JOGL::Sprite( 0, 0, 5, 5, white, "../media/PNG/Coin.png", 0 ), 2.5, AgentType::BULLET );
    _player.init( 5
                 , JOGL::Sprite ( _player_start.x, _player_start.y, 40, 40, white
                    , "../media/PNG/CharacterRight_Standing.png", 0 )
                 , bullet_sample
                 , 20 );
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
    while ( _gameState == GameState::PLAY )
    {
        _fpsLimiter.begin_frame();
        process_input();

        _camera.update();

        _collision.update();

        _player.update();

        drawGame();
        _fpsLimiter.limit();
        static int c = 0;
        if ( ++c % 10 == 0 )
        {
            //printf( "FPS: %f\n", _fpsLimiter.end_frame() );
            c = 0;
        }
    }

    for ( GLenum err; (err = glGetError()) != GL_NO_ERROR; )
    {
        fprintf( stderr, "ERROR: OpenGL error %d.\n", err );
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
                _gameState = GameState::QUIT;
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

    if ( _inputManager.is_key_presses( SDLK_w ) )
    {
        _player.set_vel_unit( glm::normalize( _player.get_vel_unit() + glm::vec2 ( 0, 1 ) ) );
    }
    if ( _inputManager.is_key_presses( SDLK_s ) )
    {
        _player.set_vel_unit( glm::normalize( _player.get_vel_unit() + glm::vec2 ( 0, -1 ) ) );
    }
    if ( _inputManager.is_key_presses( SDLK_a ) )
    {
        _player.set_vel_unit( glm::normalize( _player.get_vel_unit() + glm::vec2 ( -1, 0 ) ) );
    }
    if ( _inputManager.is_key_presses( SDLK_d ) )
    {
        _player.set_vel_unit( glm::normalize( _player.get_vel_unit() + glm::vec2 ( 1, 0 ) ) );
    }
    if ( ! _inputManager.is_key_presses( SDLK_w )
      && ! _inputManager.is_key_presses( SDLK_s )
      && ! _inputManager.is_key_presses( SDLK_a )
      && ! _inputManager.is_key_presses( SDLK_d ) )
    {
        _player.set_vel_unit( glm::vec2 ( 0, 0 ) );
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
        _player.shoot( mouseCoords );
        shot = true;
    }
    if ( ! _inputManager.is_key_presses( SDL_BUTTON_LEFT ) )
    {
        shot = false;
    }

    _camera.setPosition( _player.get_pos() );

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

    for ( auto&& s : _level.getSprites() )
    {
        _spriteBatch.add_sprite( s );
    }

    for ( auto&& b : _player.get_bullets() )
    {
        _spriteBatch.add_sprite( b.get_sprite() );
    }

    _spriteBatch.add_sprite( _player.get_sprite() );

    _spriteBatch.end();

    _spriteBatch.render_batch();

    _colorProgram->unuse();

    _window.swap();
}

MainGame::~MainGame ()
{
    SDL_Quit();
}
