#include "../inc/ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture ( std::string texturePath )
{
    return _textureCache.get_texture( texturePath );
}
