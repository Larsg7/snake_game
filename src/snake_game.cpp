#include <GL/gl.h>

#include "../inc/snake_game.h"
#include "../inc/Snake_Error.h"

Snake::Snake ( unsigned b_width, unsigned b_height )
    : _width ( b_width ), _height ( b_height ), _window ( nullptr ), _game_state ( GameState::PLAY )
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        throw Snake_Error ( "Error initiliazing SDL!" );
    }

    _window = SDL_CreateWindow( "Snake Game"
                                , SDL_WINDOWPOS_UNDEFINED
                                , SDL_WINDOWPOS_UNDEFINED
                                , 600, 600
                                , SDL_WINDOW_OPENGL );

    if ( _window == nullptr )
    {
        std::string error ( SDL_GetError() );
        throw Snake_Error ( "Could not initialize window: " + error );
    }
}

void Snake::run ()
{
    game_loop();
}

void Snake::game_loop ()
{
    while ( _game_state == GameState::PLAY )
    {
        process_input();
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

Snake::~Snake ()
{
    SDL_DestroyWindow( _window );
    SDL_Quit();
}
