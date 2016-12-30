
#include <iostream>
#include "../jaogll_texture_cache.h"
#include "../Image_loader.h"

GLTexture Texture_Cache::get_texture ( std::string texturePath )
{
    auto mit = _textureMap.find( texturePath );
    if ( mit == _textureMap.end() )
    {
        GLTexture newTexture = Image_loader::loadPNG( texturePath );
        _textureMap.insert( std::make_pair( texturePath, newTexture ) );

        std::cout << "New texture" << std::endl;

        return newTexture;
    }
    return mit->second;
}
