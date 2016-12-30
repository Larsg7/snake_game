#include <GL/glew.h>
#include <iostream>

#include "../sprite.h"
#include "../error.h"
#include "../vertex.h"
#include "../resource_manager.h"

void JOGL::Sprite::init ( float x, float y, float width, float height, std::string texture_path )
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _vboID = 0;

    _texture = ResourceManager::getTexture( texture_path );

    if ( _vboID == 0 )
    {
        glGenBuffers( 1, &_vboID );
    }

    if ( _vboID == 0 )
    {
        throw JOAGLL_ERROR ( "Could not generate buffer!" );
    }

    // vertices for a quad
    Vertex vertexData[6];

    // first triangle
    vertexData[0].setPosition( _x + _width, _y + _height );
    vertexData[0].setUV( 1.0, 1.0 );
    vertexData[1].setPosition( _x, _y + _height );
    vertexData[1].setUV( 0.0, 1.0 );
    vertexData[2].setPosition( _x, _y );
    vertexData[2].setUV( 0.0, 0.0 );

    // second triangle
    vertexData[3].setPosition( _x, _y );
    vertexData[3].setUV( 0.0, 0.0 );
    vertexData[4].setPosition( _x + _width, _y );
    vertexData[4].setUV( 1.0, 0.0 );
    vertexData[5].setPosition( _x + _width, _y + _height );
    vertexData[5].setUV( 1.0, 1.0 );

    for ( int i = 0; i < 6; ++i )
    {
       vertexData[i].setColor( 255, 255, 0, 255 );
    }

    vertexData[1].color.red = 0;

    vertexData[4].color.green = 255;

    glBindBuffer( GL_ARRAY_BUFFER, _vboID );

    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void JOGL::Sprite::draw ( GLuint attrArray )
{
    glBindTexture( GL_TEXTURE_2D, _texture.id );

    glBindBuffer( GL_ARRAY_BUFFER, _vboID );



    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

JOGL::Sprite::~Sprite ()
{
    if ( _vboID != 0 )
    {
        glDeleteBuffers( 1, &_vboID );
    }
}
