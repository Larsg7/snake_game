#include <GL/glew.h>
#include <iostream>

#include "../inc/sprite.h"
#include "../inc/Snake_Error.h"

void Sprite::init ( float x, float y, float width, float height )
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _vboID = 0;

    if ( _vboID != 0 )
    {
        glGenBuffers( 1, &_vboID );

        if ( _vboID == 0 )
        {
            throw Snake_Error ( "Could not generate buffer!"
                    , __LINE__, __FILE__ );
        }
    }

    // vertices for a quad
    float vertexData[12];

    // first triangle
    vertexData[0] = _x + _width;
    vertexData[1] = _y + _height;
    vertexData[2] = _x;
    vertexData[3] = _y + _height;
    vertexData[4] = _x;
    vertexData[5] = _y;

    // second triangle
    vertexData[6] = _x;
    vertexData[7] = _y;
    vertexData[8] = _x + _width;
    vertexData[9] = _y;
    vertexData[10] = _x + _width;
    vertexData[11] = _y + _height;

    glBindBuffer( GL_ARRAY_BUFFER, _vboID );

    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Sprite::draw ( GLuint attrArray )
{
    glBindBuffer( GL_ARRAY_BUFFER, _vboID );

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    printf("test\n");
    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

Sprite::~Sprite ()
{
    if ( _vboID != 0 )
    {
        glDeleteBuffers( 1, &_vboID );
    }
}
