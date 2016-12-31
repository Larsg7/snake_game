
#ifndef SNAKE_JAOGLL_WINDOW_H
#define SNAKE_JAOGLL_WINDOW_H

#include <string>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include "vertex.h"

namespace JOGL
{
    enum WindowFlags
    {
        INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4
    };

    class Window
    {
    public:
        virtual ~Window ();

        /**
         * \brief Creates the SDL_Window.
         * \param title  Window title
         * \param width  Window width
         * \param height Window height
         * \param flags Window flags (see enum WindowFlags)
         * \return Return Code.
         */
        int create ( std::string title, int width, int height, unsigned int flags );

        /**
         * \brief Swaps the buffer.
         * Needs to be called every frame.
         */
        void swap ();

        int get_width () const;

        int get_height () const;

        void set_clear_color ( const Color& color ) const;

    private:
        SDL_Window* _sdlWindow;

        int _width, _height;
    };
}

#endif //SNAKE_JAOGLL_WINDOW_H
