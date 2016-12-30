#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H

#include <GL/glew.h>
#include <string>

#include "sprite.h"
#include "gl_texture.h"

namespace JOGL
{
    class Sprite
    {
    public:
        Sprite ()
        {};

        virtual ~Sprite ();

        void init ( float _x, float _y, float _width, float _height, std::string texture_path );

        void draw ( GLuint attrArray );

    private:
        float _x;
        float _y;
        float _width;
        float _height;
        GLuint _vboID;
        GLTexture _texture;
    };
}

#endif //SNAKE_SPRITE_H
