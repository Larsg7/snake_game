#ifndef SNAKE_IMAGE_LOADER_H
#define SNAKE_IMAGE_LOADER_H

#include <string>

#include "gl_texture.h"

namespace JOGL
{
    class Image_Loader
    {
    public:
        /**
         * \brief Creates a GLTexture from a png file.
         * \param filePath Path to the image.
         * \return GLTexture
         */
        static GLTexture loadPNG ( std::string filePath );
    };
}

#endif //SNAKE_IMAGE_LOADER_H
