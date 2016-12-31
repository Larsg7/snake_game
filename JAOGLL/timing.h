#ifndef SNAKE_TIMING_H
#define SNAKE_TIMING_H

namespace JOGL
{
    // TODO: Limiting does not work!
    class Fps_Limiter
    {
    public:

        void init ( unsigned int targetFPS );

        void begin_frame ();

        float end_frame ();

        void set_targetFPS ( unsigned int targetFPS );

        void limit ();

    private:
        unsigned int _maxFPS;
        unsigned int _prevTicks;
    };
}

#endif //SNAKE_TIMING_H
