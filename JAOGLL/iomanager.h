#ifndef SNAKE_IOMANAGER_H
#define SNAKE_IOMANAGER_H

#include <vector>
#include <string>

namespace JOGL
{
    class IOManager
    {
    public:
        /**
         * \brief Read contents of a file into a buffer.
         * \param buffer   Vector of chars.
         * \param filePath File to read.
         * \return Bool if successful.
         */
        static bool read_file_to_buffer ( std::vector<unsigned char>& buffer, const std::string filePath );
    };
}

#endif //SNAKE_IOMANAGER_H
