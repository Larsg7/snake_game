#include <SDL2/SDL.h>
#include <vector>
#include <numeric>
#include "../jaogll.h"
#include "../error.h"

int JOGL::init ()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::string error ( SDL_GetError() );
        throw JOAGLL_ERROR( "Error initializing SDL: " + error );
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
//    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
//    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    return 0;
}
