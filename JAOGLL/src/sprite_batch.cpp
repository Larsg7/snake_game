
#include <algorithm>
#include "../sprite_batch.h"

JOGL::Render_Batch::Render_Batch ( GLuint offset, GLuint numVertices, GLuint texture )
        : offset ( offset ), numVertices ( numVertices ), texture ( texture )
{}

JOGL::Sprite_Batch::Sprite_Batch ()
        : _vbo( 0 ), _vao( 0 )
{}

void JOGL::Sprite_Batch::init ()
{
    createVertexArray();
}

void JOGL::Sprite_Batch::begin ( GlyphSortType sortType /* GlyphSortType::TEXTURE */ )
{
    _sortType = sortType;
    _renderBatches.clear();

    // no need to delete entries in _glyphs because their are smart pointers

    _glyphs.clear();
}

void JOGL::Sprite_Batch::end ()
{
    switch ( _sortType )
    {
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort( _glyphs.begin(), _glyphs.end(), []( glyph_ptr A, glyph_ptr B ) {
                return A->depth < B->depth;
            });
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort( _glyphs.begin(), _glyphs.end(), []( glyph_ptr A, glyph_ptr B ) {
                return A->depth > B->depth;
            });
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort( _glyphs.begin(), _glyphs.end(), []( glyph_ptr A, glyph_ptr B ) {
                return A->texture < B->texture;
            });
            break;
        default:
            break;
    }

    createRenderBatches();
}

void JOGL::Sprite_Batch::add_sprite ( const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
                                      const Color& color, float depth )
{
    /*  -destRect.z->
     * TL----------TR  ^
     * |            |  |
     * |            | destRect.w
     * |            |  |
     * BL----------BR
     */

    glyph_ptr newGlyph ( new JOGL::Glyph );

    newGlyph->texture = texture;
    newGlyph->depth = depth;

    newGlyph->topLeft.color = color;
    newGlyph->topLeft.setPosition( destRect.x, destRect.y + destRect.w );
    newGlyph->topLeft.setUV( uvRect.x, uvRect.y + uvRect.w );

    newGlyph->bottomLeft.color = color;
    newGlyph->bottomLeft.setPosition( destRect.x, destRect.y );
    newGlyph->bottomLeft.setUV( uvRect.x, uvRect.y );

    newGlyph->topRight.color = color;
    newGlyph->topRight.setPosition( destRect.x + destRect.z, destRect.y + destRect.w );
    newGlyph->topRight.setUV( uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    newGlyph->bottomRight.color = color;
    newGlyph->bottomRight.setPosition( destRect.x + destRect.z, destRect.y );
    newGlyph->bottomRight.setUV( uvRect.x + uvRect.z, uvRect.y );

    _glyphs.push_back( newGlyph );
}

void JOGL::Sprite_Batch::render_batch ()
{
    glBindVertexArray( _vao );

    for ( auto& r : _renderBatches )
    {
        glBindTexture( GL_TEXTURE_2D, r.texture );
        glDrawArrays( GL_TRIANGLES, r.offset, r.numVertices );
    }

    glBindVertexArray( 0 );
}

void JOGL::Sprite_Batch::createRenderBatches ()
{
    std::vector<Vertex> vertices ( _glyphs.size() * 6 );

    if ( _glyphs.empty() )
    {
        return;
    }

    int offset = 0;
    int cv = 0; // current vertex
    _renderBatches.emplace_back( offset, 6, _glyphs[0]->texture );
    vertices[cv++] = _glyphs[0]->topLeft;
    vertices[cv++] = _glyphs[0]->bottomLeft;
    vertices[cv++] = _glyphs[0]->bottomRight;
    vertices[cv++] = _glyphs[0]->bottomRight;
    vertices[cv++] = _glyphs[0]->topRight;
    vertices[cv++] = _glyphs[0]->topLeft;
    offset += 6;

    for ( int cg = 1; cg < _glyphs.size(); ++cg, offset += 6 ) // current glyph
    {
        if ( _glyphs[cg]->texture != _glyphs[cg-1]->texture )
        {
            _renderBatches.emplace_back( 0, 6, _glyphs[cg]->texture );
        }
        else
        {
            _renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = _glyphs[cg]->topLeft;
        vertices[cv++] = _glyphs[cg]->bottomLeft;
        vertices[cv++] = _glyphs[cg]->bottomRight;
        vertices[cv++] = _glyphs[cg]->bottomRight;
        vertices[cv++] = _glyphs[cg]->topRight;
        vertices[cv++] = _glyphs[cg]->topLeft;
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    // orphan the buffer
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW );
    // upload data
    glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data() );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void JOGL::Sprite_Batch::createVertexArray ()
{
    if ( _vao == 0)
    {
        glGenVertexArrays( 1, &_vao );
    }
    glBindVertexArray( _vao );

    if ( _vbo == 0 )
    {
        glGenBuffers( 1, &_vbo );
    }
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    // This is the position attribute pointer
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)offsetof( Vertex, position ) );
    // This is the color attribute pointer
    glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), (void*)offsetof( Vertex, color ) );
    // This is the UV attribute pointer
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)offsetof( Vertex, uv ) );

    glBindVertexArray( 0 );
}

JOGL::Sprite_Batch::~Sprite_Batch ()
{

}
