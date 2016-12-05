#ifndef SNAKE_SNAKE_GAME_H
#define SNAKE_SNAKE_GAME_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include "GLSLCompiler.h"

enum class GameState {PLAY, QUIT};

class Snake
{
public:
    Snake ( unsigned b_width, unsigned b_height );

    /**
     * \brief Game's main entry point.
     * Handles Menus and the game loop.
     */
    void run ();

    void initShaders ();

    /**
     * \brief Contains the game loop.
     */
    void game_loop ();

    /**
     * \brief Contains logic to handle input.
     */
    void process_input ();

    void drawGame ();

    virtual ~Snake ();

private:
    GLuint _vaoID;
    /** Main game window */
    SDL_Window* _window;

    /** Board dimensions */
    const unsigned _board_width;
    const unsigned  _board_height;

    /** Current game state */
    GameState _game_state;

    Sprite _sprite;

    GLSLCompiler _colorProgram;
};


#endif //SNAKE_SNAKE_GAME_H