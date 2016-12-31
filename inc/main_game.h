#ifndef SNAKE_SNAKE_GAME_H
#define SNAKE_SNAKE_GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <jaogll/glsl_compiler.h>
#include <jaogll/gl_texture.h>
#include <jaogll/window.h>
#include <jaogll/camera2D.h>
#include <jaogll/sprite_batch.h>
#include <jaogll/input_manager.h>
#include <jaogll/timing.h>
#include "level.h"

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

    void add_sprite (  );

    virtual ~MainGame ();

private:
    /** Main game window */
    JOGL::Window _window;

    /** Current game state */
    GameState _gameState;

    /** Screen dimensions */
    const unsigned _w_width;
    const unsigned _w_height;

    JOGL::Fps_Limiter _fpsLimiter;

    JOGL::Camera2D _camera;

    JOGL::Sprite_Batch _spriteBatch;

    JOGL::Input_Manager _inputManager;

    JOGL::GLSLCompiler* _colorProgram;

    Level _level;

    unsigned MAX_FPS;
};


#endif //SNAKE_SNAKE_GAME_H