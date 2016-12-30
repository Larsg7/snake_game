#ifndef SNAKE_IMAGE_LOADER_H
#define SNAKE_IMAGE_LOADER_H

#include <string>

#include "gl_texture.h"

namespace JOGL
{
    class Image_Loader
    {
    public:
        static GLTexture loadPNG ( std::string filePath );
    };
}

#endif //SNAKE_IMAGE_LOADER_H
