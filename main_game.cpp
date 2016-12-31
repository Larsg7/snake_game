#include <GL/glew.h>
#include <iostream>
#include <numeric>

#include "main_game.h"
#include "JAOGLL/error.h"
#include "JAOGLL/jaogll.h"
#include "JAOGLL/resource_manager.h"
#include <glm/glm.hpp>


MainGame::MainGame ( unsigned w_width, unsigned w_height )
    : _w_width ( w_width )
      , _w_height ( w_height )
      , MAX_FPS ( 60 )
      , _gameState ( GameState::PLAY )
{
    JOGL::init();

    _window.create( "Game Engine", _w_width, _w_height, 0 );

    initShaders();

    _camera.init( w_width, w_height );

    _spriteBatch.init();

    _fpsLimiter.init( MAX_FPS );
}

void MainGame::initShaders ()
{
    _colorProgram.compileShaders( "../shaders/colorShading.vert", "../shaders/colorShading.frag" );
    _colorProgram.addAttribute( "vertexPosition" );
    _colorProgram.addAttribute( "vertexColor" );
    _colorProgram.addAttribute( "vertexUV" );
    _colorProgram.linkShaders();
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
        printf( "%f : %f\n", mouseCoords.x, mouseCoords.y );
    }

    return 0;
}

void MainGame::add_sprite ( JOGL::Sprite* sprite )
{

}

void MainGame::drawGame ()
{
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _colorProgram.use();

    // set texture
    glActiveTexture( GL_TEXTURE0 );
    GLint textureLocation = _colorProgram.get_uniformLocation( "mySampler" );
    glUniform1i( textureLocation, 0 );

    // set camera matrix
    GLint pLocation = _colorProgram.get_uniformLocation( "P" );
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv( pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]) );

    _spriteBatch.begin();

    glm::vec4 pos ( 0.0f, 0.0f, 50.0f, 50.0f );
    glm::vec4 uv ( 0.0f, 0.0f ,1.0f, 1.0f );
    static JOGL::GLTexture texture = JOGL::ResourceManager::getTexture( "../media/PNG/CharacterRight_Standing.png" );
    JOGL::Color color;
    color.red = 255;
    color.alpha = 255;
    color.blue = 255;
    color.green = 255;
    for ( int i = 0; i < 1; ++i )
    {
        _spriteBatch.draw( pos + glm::vec4(0,0,0,0), uv, texture.id, color, 0.0f );
    }

    _spriteBatch.end();

    _spriteBatch.render_batch();

    glBindTexture( GL_TEXTURE_2D, 0 );

    _colorProgram.unuse();

    _window.swap();
}

MainGame::~MainGame ()
{
    SDL_Quit();
}
