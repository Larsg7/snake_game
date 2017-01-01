#include <GL/glew.h>
#include <iostream>
#include <numeric>

#include "zombie_game/inc/main_game.h"
#include <jaogll/error.h>
#include <jaogll/jaogll.h>
#include <jaogll/resource_manager.h>
#include <jaogll/logger.h>
#include <jaogll/sprite.h>
#include <glm/glm.hpp>


MainGame::MainGame ( unsigned w_width, unsigned w_height )
    : _w_width ( w_width )
      , _w_height ( w_height )
      , MAX_FPS ( 60 )
      , _gameState ( GameState::PLAY )
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
        _camera.setPosition( _camera.getPosition() + glm::vec2( 0.0, CAMERA_SPEED ) );
    }
    if ( _inputManager.is_key_presses( SDLK_s ) )
    {
        _camera.setPosition( _camera.getPosition() + glm::vec2 ( 0.0, -CAMERA_SPEED ) );
    }
    if ( _inputManager.is_key_presses( SDLK_a ) )
    {
        _camera.setPosition( _camera.getPosition() + glm::vec2 ( -CAMERA_SPEED, 0.0 ) );
    }
    if ( _inputManager.is_key_presses( SDLK_d ) )
    {
        _camera.setPosition( _camera.getPosition() + glm::vec2 ( CAMERA_SPEED, 0.0 ) );
    }
    if ( _inputManager.is_key_presses( SDLK_q ) )
    {
        _camera.setScale( _camera.getScale() + SCALE_SPEED );
    }
    if ( _inputManager.is_key_presses( SDLK_e ) )
    {
        _camera.setScale( _camera.getScale() - SCALE_SPEED );
    }
    if ( _inputManager.is_key_presses( SDL_BUTTON_LEFT ) )
    {
        glm::vec2 mouseCoords = _inputManager.get_mouse_coords();
        mouseCoords = _camera.convert_screen_to_world( mouseCoords );
    }

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
    
    for ( auto& s : _level.getSprites() )
    {
        _spriteBatch.add_sprite( s.pos, s.uv, s.texture.id, s.color, 1 );
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
