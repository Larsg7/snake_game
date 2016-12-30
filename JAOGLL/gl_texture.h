#ifndef SNAKE_GL_TEXTURE_H
#define SNAKE_GL_TEXTURE_H

#include <GL/glew.h>

namespace JOGL
{
    struct GLTexture
    {
        GLuint id;
        int width;
        int height;
    };
}

#endif //SNAKE_GL_TEXTURE_H
