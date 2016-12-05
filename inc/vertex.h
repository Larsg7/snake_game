#ifndef SNAKE_VERTEX_H
#define SNAKE_VERTEX_H

#include <GL/gl.h>

/**
 * \brief Struct holding information about a vertex
 * Needs to be multiple of 4 bytes in size
 */
struct Vertex
{
    struct Position
    {
        float x;
        float y;
    } position;

    struct Color
    {
        GLubyte red;
        GLubyte green;
        GLubyte blue;
        GLubyte alpha;
    } color;
};

#endif //SNAKE_VERTEX_H
