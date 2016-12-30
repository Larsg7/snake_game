
#include <SDL2/SDL_timer.h>
#include <numeric>
#include <vector>
#include "../timing.h"

void JOGL::Fps_Limiter::init ( unsigned int targetFPS )
{
    set_targetFPS( targetFPS );
}

void JOGL::Fps_Limiter::begin_frame ()
{
    _prevTicks = SDL_GetTicks();
}

float JOGL::Fps_Limiter::end_frame ()
{
    return 1000.0f / ( SDL_GetTicks() - _prevTicks );
}

void JOGL::Fps_Limiter::limit ()
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

    float wait = (1000.0f / _maxFPS) - average_frameTime;

    SDL_Delay( (wait > 0) ? static_cast<unsigned>(wait) : 0 );

    //std::cout << wait << std::endl;

    previous_ticks = SDL_GetTicks();
}

void JOGL::Fps_Limiter::set_targetFPS ( unsigned int targetFPS )
{
    Fps_Limiter::_maxFPS = targetFPS;
}
