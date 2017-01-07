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
#include "player.h"
#include "collision_manager.h"
#include "zombie.h"
#include "agent_manager.h"

enum class GameState {PLAY, QUIT};



class MainGame
{
public:
    MainGame ( unsigned w_width, unsigned w_height );

    void init_agents ();

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

private:
    void collide ();

    void zombie_follow ();

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

    Collision_Manager _collision;

    Agent_Manager _agent_manager;

    Player* _player;
    const glm::vec2 _player_start;

    std::vector<Zombie*> _zombies;

    unsigned MAX_FPS;
};


#endif //SNAKE_SNAKE_GAME_H