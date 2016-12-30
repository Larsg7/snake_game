#include <GL/glew.h>
#include <iostream>
#include <numeric>

#include "../main_game.h"
#include "../jaogll_error.h"

MainGame::MainGame ( unsigned b_width, unsigned b_height )
    : _board_width ( b_width )
      , _board_height ( b_height )
      , _window ( nullptr )
      , _game_state ( GameState::PLAY )
      , _vaoID ( 0 )
      , MAX_FPS ( 60 )
{
    // for some reason errors don't work here

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::string error ( SDL_GetError() );
        throw Error ( "Error initializing SDL: " + error );
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
//    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
//    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    _window = SDL_CreateWindow( "Snake Game"
                                , SDL_WINDOWPOS_UNDEFINED
                                , SDL_WINDOWPOS_UNDEFINED
                                , 600, 600
                                , SDL_WINDOW_OPENGL );

    if ( _window == nullptr )
    {
        throw Error ( "Could not initialize window: " + std::string( SDL_GetError() ) );
    }

    /* OpenGL initializations */

    SDL_GLContext glContext = SDL_GL_CreateContext( _window );

    if ( glContext == nullptr )
    {
        throw Error ( "SDL_GLContext could not be created: " + std::string( SDL_GetError() ) );
    }

    glewExperimental = GL_TRUE;

    if ( glewInit() != GLEW_OK )
    {
        throw Error ( "Could not init glew!" );
    }

    glGenVertexArrays( 1, &_vaoID );
    glBindVertexArray( _vaoID );

    printf( "*** OpenGL Info ***\nVersion: %s\n\n", glGetString( GL_VERSION ) );

    glClearColor( 0, 0, 1, 1 );

    // set vsync
    SDL_GL_SetSwapInterval( 1 );

    initShaders();
}

void MainGame::initShaders ()
{
    _colorProgram.compileShaders( "../shaders/colorShading.vert", "../shaders/colorShading.frag" );
    _colorProgram.addAttribute( "vertexPosition" );
    _colorProgram.addAttribute( "vertexColor" );
    _colorProgram.addAttribute( "vertexUV" );
    _colorProgram.linkShaders();
}

void MainGame::run ()
{
    _sprites.push_back( new Sprite() );
    _sprites.back()->init( -1, -1, 1, 1, "../media/PNG/CharacterRight_Standing.png" );

    _sprites.push_back( new Sprite() );
    _sprites.back()->init( 0, 0, 1, 1, "../media/PNG/CharacterRight_Standing.png" );

    game_loop();
}

void MainGame::game_loop ()
{
    while ( _game_state == GameState::PLAY )
    {
        process_input();
        drawGame();
        limitFPS();
    }

    for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
    {
        fprintf( stderr, "ERROR: OpenGL error %d.\n", err );
    }
}

void MainGame::limitFPS ()
{
    static const int NUM_SAMPLES = 10;
    static std::vector<float> frameTimes (NUM_SAMPLES);

    static float previous_ticks = SDL_GetTicks();

    static int frameTimes_pos = 0;
    static int count = 1;

    frameTimes[(frameTimes_pos %= NUM_SAMPLES)] = SDL_GetTicks() - previous_ticks;
    frameTimes_pos++;

    float average_frameTime = std::accumulate( frameTimes.begin(), frameTimes.end(), 0.0f )
                              / ((count > NUM_SAMPLES) ? NUM_SAMPLES : count++);

    float wait = (1000.0f / MAX_FPS) - average_frameTime;

    SDL_Delay( (wait > 0) ? static_cast<unsigned>(wait) : 0 );

    //std::cout << wait << std::endl;

    previous_ticks = SDL_GetTicks();
}

void MainGame::process_input ()
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

void MainGame::drawGame ()
{
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _colorProgram.use();
    glActiveTexture( GL_TEXTURE0 );
    GLint textureLocation = _colorProgram.get_uniformLocation( "mySampler" );
    glUniform1i( textureLocation, 0 );

    //GLint timeLocation = _colorProgram.get_uniformLocation( "time" );

    //glUniform1f( timeLocation, _time );

    for ( auto&& sprite : _sprites )
    {
        sprite->draw( 0 );
    }

    glBindTexture( GL_TEXTURE_2D, 0 );

    _colorProgram.unuse();

    SDL_GL_SwapWindow( _window );
}

MainGame::~MainGame ()
{
    SDL_DestroyWindow( _window );
    SDL_Quit();
}
