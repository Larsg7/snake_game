

#include "../window.h"
#include "../window.h"
#include "../error.h"
#include "../logger.h"

int JOGL::Window::create ( std::string title, int width, int height, unsigned int flags )
{
    _width = width;
    _height = height;

    Uint32 window_flags = SDL_WINDOW_OPENGL;

    // set custom window flags
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
        throw JOAGLL_ERROR ( "Could not initialize SDL_Window: " + std::string( SDL_GetError() ) );
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
        throw JOAGLL_ERROR ( "Could not initialize glew!" );
    }

    printf( "*** OpenGL Info ***\nVersion: %s\n\n", glGetString( GL_VERSION ) );

    // set default (white)
    glClearColor( 1, 1, 1, 1 );

    // set vsync
    SDL_GL_SetSwapInterval( 1 );

    // enable alpha blending
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    JOGL::Logger::log( "Window created!", LogLevel::LOG_INFO );

    return 0;
}

void JOGL::Window::swap ()
{
    SDL_GL_SwapWindow( _sdlWindow );

    // clear window
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

int JOGL::Window::get_width () const
{
    return _width;
}

int JOGL::Window::get_height () const
{
    return _height;
}

void JOGL::Window::set_clear_color ( const Color& color ) const
{
    glClearColor( color.red   / 255.0f
                , color.green / 255.0f
                , color.blue  / 255.0f
                , color.alpha / 255.0f );
}

JOGL::Window::~Window ()
{
    SDL_DestroyWindow( _sdlWindow );
}