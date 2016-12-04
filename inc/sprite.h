#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H

#include <GL/glew.h>

#include "../inc/sprite.h"

class Sprite
{
public:
    Sprite () {};

    virtual ~Sprite ();

    void init ( float _x, float _y, float _width, float _height );

    void draw ();

private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
};


#endif //SNAKE_SPRITE_H
