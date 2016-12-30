

#include "../window.h"
#include "../window.h"
#include "../error.h"

int JOGL::Window::create ( std::string title, int width, int height, unsigned int flags )
{
    _width = width;
    _height = height;

    Uint32 window_flags = SDL_WINDOW_OPENGL;

    if ( flags & INVISIBLE )
    {
        window_flags |= SDL_WINDOW_HIDDEN;
    }
    if ( flags & FULLSCREEN )
    {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }
    if ( flags & BORDERLESS )
    {
        window_flags |= SDL_WINDOW_BORDERLESS;
    }

    _sdlWindow = SDL_CreateWindow( title.c_str()
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , _width, _height
            , window_flags );

    if ( _sdlWindow == nullptr )
    {
        throw JOAGLL_ERROR ( "Could not initialize window: " + std::string( SDL_GetError() ) );
    }

    /* OpenGL initializations */

    SDL_GLContext glContext = SDL_GL_CreateContext( _sdlWindow );

    if ( glContext == nullptr )
    {
        throw JOAGLL_ERROR ( "SDL_GLContext could not be created: " + std::string( SDL_GetError() ) );
    }

    glewExperimental = GL_TRUE;

    if ( glewInit() != GLEW_OK )
    {
        throw JOAGLL_ERROR ( "Could not init glew!" );
    }

    printf( "*** OpenGL Info ***\nVersion: %s\n\n", glGetString( GL_VERSION ) );

    glGenVertexArrays( 1, &_vaoID );
    glBindVertexArray( _vaoID );

    glClearColor( 0, 0, 1, 1 );

    // set vsync
    SDL_GL_SetSwapInterval( 0 );

    // enable alpha blending
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    return 0;
}

void JOGL::Window::swap ()
{
    SDL_GL_SwapWindow( _sdlWindow );
}

int JOGL::Window::get_width () const
{
    return _width;
}

int JOGL::Window::get_height () const
{
    return _height;
}

JOGL::Window::~Window ()
{
    SDL_DestroyWindow( _sdlWindow );
}