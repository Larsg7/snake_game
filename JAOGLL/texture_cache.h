
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
        GLTexture get_texture ( std::string texturePath );

    private:
        std::map<std::string, GLTexture> _textureMap;
    };
}

#endif //SNAKE_TEXTURECACHE_H
