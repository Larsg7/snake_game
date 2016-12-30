#include "../jaogll_iomanager.h"
#include "../jaogll_error.h"

#include <fstream>

bool IOManager::read_file_to_buffer ( std::vector<unsigned char>& buffer, const std::string filePath )
{
    std::fstream file ( filePath, std::ios::binary | std::ios::in );

    if ( file.fail() )
    {
        throw Error ( "Could not open file '" + filePath + "'!" );
    }

    file.seekg( 0, std::ios::end );

    long fileSize = file.tellg();

    file.seekg( 0, std::ios::beg );

    // Reduce by header size
    fileSize -= file.tellg();

    buffer.resize( fileSize );

    file.read( (char*)&(buffer[0]), fileSize );

    file.close();

    return true;
}
