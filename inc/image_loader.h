//
// Created by lars on 12/7/16.
//

#ifndef SNAKE_IMAGE_LOADER_H
#define SNAKE_IMAGE_LOADER_H

#include <string>

#include "gl_texture.h"

class image_loader
{
    static GLTexture loadPNG ( std::string filePath );
};


#endif //SNAKE_IMAGE_LOADER_H
