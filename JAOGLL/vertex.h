#ifndef SNAKE_VERTEX_H
#define SNAKE_VERTEX_H

#include <GL/gl.h>


namespace JOGL
{
    /**
     * \brief Struct holding information about a specific color.
     */
    struct Color
    {
        Color ()
        {}

        Color ( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha )
                : red( red ), green( green ), blue( blue ), alpha( alpha )
        {}

        GLubyte red;
        GLubyte green;
        GLubyte blue;
        GLubyte alpha;
    };

    struct Position
    {
        Position ()
        {}

        Position ( float x, float y )
                : x( x ), y( y )
        {}

        float x;
        float y;
    };

    /**
     * \brief Position of the texture
     */
    struct UV
    {
        UV ()
        {}

        UV ( float u, float v )
                : u( u ), v( v )
        {}

        float u;
        float v;
    };

    /**
     * \brief Struct holding information about a vertex
     * Needs to be multiple of 4 bytes in size
     */
    struct Vertex
    {
        Vertex ()
        {}

        Vertex ( const Position& position, const Color& color, const UV& uv )
                : position( position ), color( color ), uv( uv )
        {}

        Position position;

        Color color;

        UV uv;

        void setColor ( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
        {
            color.red = r;
            color.green = g;
            color.blue = b;
            color.alpha = a;
        }

        void setPosition ( float x, float y )
        {
            position.x = x;
            position.y = y;
        }

        void setUV ( float u, float v )
        {
            uv.u = u;
            uv.v = v;
        }
    };
}

#endif //SNAKE_VERTEX_H
