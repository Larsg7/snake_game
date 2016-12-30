#ifndef SNAKE_TIMING_H
#define SNAKE_TIMING_H

namespace JOGL
{
    class Fps_Limiter
    {
    public:

        void init ( unsigned int targetFPS );

        void begin_frame ();

        float end_frame ();

        void set_targetFPS ( unsigned int targetFPS );

        /**
         * \brief
         * \return Number of FPS.
         */
        void limit ();

    private:
        unsigned int _maxFPS;
        unsigned int _prevTicks;
    };
}

#endif //SNAKE_TIMING_H
