
#ifndef SNAKE_RESOURCEMANAGER_H
#define SNAKE_RESOURCEMANAGER_H

#include <string>
#include "texture_cache.h"


namespace JOGL
{
    class ResourceManager
    {
    public:
        static GLTexture getTexture ( std::string texturePath );

    private:
        static Texture_Cache _textureCache;
    };
}

#endif //SNAKE_RESOURCEMANAGER_H
