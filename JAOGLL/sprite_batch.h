//
// Created by lars on 12/30/16.
//

#ifndef SNAKE_SPRITE_BATCH_H
#define SNAKE_SPRITE_BATCH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "vertex.h"

namespace JOGL
{
    /**
     * \brief Different sorting types for the textures in render_batch.
     */
    enum class GlyphSortType
    {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    /**
     * \brief Struct holding information about a texture.
     */
    struct Glyph
    {
        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

    typedef std::shared_ptr<Glyph> glyph_ptr;

    /**
     * \brief Struct holding information about a render batch.
     */
    struct Render_Batch
    {
        Render_Batch ( GLuint offset, GLuint numVertices, GLuint texture );

        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class Sprite_Batch
    {
    public:
        Sprite_Batch ();

        virtual ~Sprite_Batch ();

        /**
         * \brief Calls createVertexArray.
         */
        void init ();

        /**
         * \brief Clears the vectors and sets sort type.
         * \param sortType
         */
        void begin ( GlyphSortType sortType = GlyphSortType::TEXTURE );

        /**
         * \brief Sorts _glyphs and calls createRenderBatches.
         */
        void end ();

        /**
         * \brief Creates a Glyph based on the arguments and stores it in _glyphs.
         * \param destRect Destination rectangle. x and y are the pos of the bottom left corner, z is the width and
         *                 w the height of the rectangle.
         * \param uvRect   UV coordinates, same as for destRect.
         * \param texture  Texture of the sprite.
         * \param color    Color of the sprite.
         * \param depth    Depth of the sprite.
         */
        void add_sprite ( const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const Color& color,
                          float depth );

        /**
         * \brief Binds _vao and draws Render_Batches.
         */
        void render_batch ();

    private:
        void createRenderBatches ();
        void createVertexArray ();

        GLuint _vbo;
        GLuint _vao;

        GlyphSortType _sortType;

        std::vector<glyph_ptr> _glyphs;
        std::vector<Render_Batch> _renderBatches;
    };
}

#endif //SNAKE_SPRITE_BATCH_H
