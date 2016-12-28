#include "../inc/Image_loader.h"
#include "../inc/picoPNG.h"
#include "../inc/iomanager.h"
#include "../inc/Snake_Error.h"

GLTexture Image_loader::loadPNG ( std::string filePath )
{
    GLTexture texture = {};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;

    unsigned long width, height;

    try
    {
        IOManager::read_file_to_buffer( in, filePath );
    }
    catch ( const Snake_Error& e )
    {
        fprintf( stderr, "Error reading image '%s'\n", filePath.c_str() );
        throw e;
    }

    int error = decodePNG( out, width, height, &(in[0]), in.size(), true );

    if ( error != 0 )
    {
        throw Snake_Error ( "decodePNG failed with error '" + std::to_string( error ) + "'!"
                , __LINE__, __FILE__ );
    }

    glGenTextures( 1, &(texture.id) );

    glBindTexture( GL_TEXTURE_2D, texture.id );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(width), static_cast<int>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]) );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, 0 );

    texture.width = static_cast<int>(width);
    texture.height = static_cast<int>(height);

    return texture;
}
