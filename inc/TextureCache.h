
#ifndef SNAKE_TEXTURECACHE_H
#define SNAKE_TEXTURECACHE_H


#include <map>
#include "gl_texture.h"

class TextureCache
{
public:
    GLTexture get_texture ( std::string texturePath );

private:
    std::map<std::string, GLTexture> _textureMap;
};


#endif //SNAKE_TEXTURECACHE_H
