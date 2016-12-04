#ifndef SNAKE_SNAKE_GAME_H
#define SNAKE_SNAKE_GAME_H

#include <SDL2/SDL.h>

enum class GameState {PLAY, QUIT};

class Snake
{
public:
    Snake ( unsigned b_width, unsigned b_height );

    void run();

    void game_loop ();

    void process_input ();

    virtual ~Snake ();

private:
    SDL_Window* _window;
    const unsigned _width;
    const unsigned  _height;
    GameState _game_state;
};


#endif //SNAKE_SNAKE_GAME_H
