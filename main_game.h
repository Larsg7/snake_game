#ifndef SNAKE_SNAKE_GAME_H
#define SNAKE_SNAKE_GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "JAOGLL/sprite.h"
#include "JAOGLL/glsl_compiler.h"
#include "JAOGLL/gl_texture.h"
#include "JAOGLL/window.h"
#include "JAOGLL/camera2D.h"
#include "JAOGLL/sprite_batch.h"
#include "JAOGLL/input_manager.h"
#include "JAOGLL/timing.h"

enum class GameState {PLAY, QUIT};

class MainGame
{
public:
    MainGame ( unsigned w_width, unsigned w_height );

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
    int process_input ();

    void drawGame ();

    virtual ~MainGame ();

    void add_sprite ( JOGL::Sprite* sprite );

private:
    /** Main game window */
    JOGL::Window _window;

    /** Current game state */
    GameState _gameState;

    /** Board dimensions */
    const unsigned _w_width;
    const unsigned _w_height;

    JOGL::Fps_Limiter _fpsLimiter;

    JOGL::Camera2D _camera;

    JOGL::Sprite_Batch _spriteBatch;

    JOGL::Input_Manager _inputManager;

    JOGL::GLSLCompiler _colorProgram;

    unsigned MAX_FPS;
};


#endif //SNAKE_SNAKE_GAME_H