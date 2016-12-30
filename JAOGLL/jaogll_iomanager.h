#ifndef SNAKE_IOMANAGER_H
#define SNAKE_IOMANAGER_H

#include <vector>
#include <string>

class IOManager
{
public:
    static bool read_file_to_buffer ( std::vector<unsigned char>& buffer, const std::string filePath );
};

#endif //SNAKE_IOMANAGER_H
