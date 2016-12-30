
#ifndef SNAKE_JAOGLL_WINDOW_H
#define SNAKE_JAOGLL_WINDOW_H

#include <string>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>

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

        int create ( std::string title, int width, int height, unsigned int flags );

        void swap ();

        int get_width () const;

        int get_height () const;

    private:
        SDL_Window* _sdlWindow;

        int _width, _height;

        GLuint _vaoID;
    };
}

#endif //SNAKE_JAOGLL_WINDOW_H
