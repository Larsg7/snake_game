#include "../jaogll_resource_manager.h"

Texture_Cache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture ( std::string texturePath )
{
    return _textureCache.get_texture( texturePath );
}
