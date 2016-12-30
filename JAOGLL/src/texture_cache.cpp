
#include <iostream>
#include "../texture_cache.h"
#include "../image_loader.h"

JOGL::GLTexture JOGL::Texture_Cache::get_texture ( std::string texturePath )
{
    auto mit = _textureMap.find( texturePath );
    if ( mit == _textureMap.end() )
    {
        JOGL::GLTexture newTexture = Image_Loader::loadPNG( texturePath );
        _textureMap.insert( std::make_pair( texturePath, newTexture ) );

        return newTexture;
    }
    return mit->second;
}
