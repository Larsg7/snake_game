#include <GL/glew.h>
#include <iostream>

#include "../sprite.h"
#include "../jaogll_error.h"
#include "../jaogll_vertex.h"
#include "../resource_manager.h"

void Sprite::init ( float x, float y, float width, float height, std::string texture_path )
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
        throw Jaogll_Error ( "Could not generate buffer!"
                , __LINE__, __FILE__ );
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

void Sprite::draw ( GLuint attrArray )
{
    glBindTexture( GL_TEXTURE_2D, _texture.id );

    glBindBuffer( GL_ARRAY_BUFFER, _vboID );

    glEnableVertexAttribArray( 0 );

    // This is the position attribute pointer
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)offsetof( Vertex, position ) );
    // This is the color attribute pointer
    glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), (void*)offsetof( Vertex, color ) );
    // This is the UV attribute pointer
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)offsetof( Vertex, uv ) );

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
