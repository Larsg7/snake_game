
#ifndef SNAKE_TEXTURECACHE_H
#define SNAKE_TEXTURECACHE_H


#include <map>
#include <string>
#include "gl_texture.h"

namespace JOGL
{
    class Texture_Cache
    {
    public:
        /**
         * \brief Returns a GLTexture if one corresponding to the path is found in _textureMap
         *        or creates a new one and stores it in _textureMap.
         * \param texturePath Path to the image.
         * \return GLTexture
         */
        GLTexture get_texture ( std::string texturePath );

    private:
        std::map<std::string, GLTexture> _textureMap;
    };
}

#endif //SNAKE_TEXTURECACHE_H
