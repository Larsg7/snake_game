
#ifndef SNAKE_RESOURCEMANAGER_H
#define SNAKE_RESOURCEMANAGER_H

#include <string>
#include "texture_cache.h"


namespace JOGL
{
    class ResourceManager
    {
    public:
        /**
         * \brief Returns a texture if inside the texture cache or creates a new one.
         * Actually just a wrapper for Texture_Cache::getTexture.
         * \param texturePath Path to the image file.
         * \return GLTexture
         */
        static GLTexture getTexture ( std::string texturePath );

    private:
        static Texture_Cache _textureCache;
    };
}

#endif //SNAKE_RESOURCEMANAGER_H
