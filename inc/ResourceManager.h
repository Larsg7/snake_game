
#ifndef SNAKE_RESOURCEMANAGER_H
#define SNAKE_RESOURCEMANAGER_H


#include "TextureCache.h"

class ResourceManager
{
public:
    static GLTexture getTexture ( std::string texturePath );

private:
    static TextureCache _textureCache;
};


#endif //SNAKE_RESOURCEMANAGER_H
