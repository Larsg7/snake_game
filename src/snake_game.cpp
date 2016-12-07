#include <GL/glew.h>
#include <iostream>

#include "../inc/snake_game.h"
#include "../inc/Snake_Error.h"

Snake::Snake ( unsigned b_width, unsigned b_height )
    : _board_width ( b_width )
      , _board_height ( b_height )
      , _window ( nullptr )
      , _game_state ( GameState::PLAY )
      , _vaoID ( 0 )
      , _time ( 0 )
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::string error ( SDL_GetError() );
        throw Snake_Error ( "Error initializing SDL: " + error
                , __LINE__, __FILE__ );
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    _window = SDL_CreateWindow( "Snake Game"
                                , SDL_WINDOWPOS_UNDEFINED
                                , SDL_WINDOWPOS_UNDEFINED
                                , 600, 600
                                , SDL_WINDOW_OPENGL );

    if ( _window == nullptr )
    {
        throw Snake_Error ( "Could not initialize window: " + std::string( SDL_GetError() )
                , __LINE__, __FILE__ );
    }

    /* OpenGL initializations */

    SDL_GLContext glContext = SDL_GL_CreateContext( _window );

    if ( glContext == nullptr )
    {
        throw Snake_Error ( "SDL_GLContext could not be created: " + std::string( SDL_GetError() )
                , __LINE__, __FILE__ );
    }

    glewExperimental = GL_TRUE;

    if ( glewInit() != GLEW_OK )
    {
        throw Snake_Error ( "Could not init glew!"
                , __LINE__, __FILE__ );
    }

    glGenVertexArrays( 1, &_vaoID );
    glBindVertexArray( _vaoID );

    glClearColor( 0, 0, 1, 1 );

    initShaders();
}

void Snake::initShaders ()
{
    _colorProgram.compileShaders( "../shaders/colorShading.vert", "../shaders/colorShading.frag" );
    _colorProgram.addAttribute( "vertexPosition" );
    _colorProgram.addAttribute( "vertexColor" );
    _colorProgram.linkShaders();
}

void Snake::run ()
{
    _sprite.init( -1, -1, 2, 2 );

    game_loop();
}

void Snake::game_loop ()
{
    while ( _game_state == GameState::PLAY )
    {
        process_input();
        _time += 0.001;
        drawGame();
        //SDL_Delay( 50 );
    }

    for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
    {
        fprintf( stderr, "ERROR: OpenGL error %d.\n", err );
    }
}

void Snake::process_input ()
{
    SDL_Event event;

    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:
                _game_state = GameState::QUIT;
                break;
            default:
                break;
        }
    }
}

void Snake::drawGame ()
{
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _colorProgram.use();

    GLint timeLocation = _colorProgram.get_uniformLocation( "time" );

    glUniform1f( timeLocation, _time );

    _sprite.draw( 0 );

    _colorProgram.unuse();

    SDL_GL_SwapWindow( _window );
}

Snake::~Snake ()
{
    SDL_DestroyWindow( _window );
    SDL_Quit();
}