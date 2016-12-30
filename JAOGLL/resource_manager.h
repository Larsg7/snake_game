
#ifndef SNAKE_RESOURCEMANAGER_H
#define SNAKE_RESOURCEMANAGER_H


#include "jaogll_texture_cache.h"

class ResourceManager
{
public:
    static GLTexture getTexture ( std::string texturePath );

private:
    static Texture_Cache _textureCache;
};


#endif //SNAKE_RESOURCEMANAGER_H
