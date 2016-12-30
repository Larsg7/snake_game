#include "../resource_manager.h"

JOGL::Texture_Cache JOGL::ResourceManager::_textureCache;

JOGL::GLTexture JOGL::ResourceManager::getTexture ( std::string texturePath )
{
    return _textureCache.get_texture( texturePath );
}
