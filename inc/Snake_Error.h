#ifndef SNAKE_SNAKE_ERROR_H
#define SNAKE_SNAKE_ERROR_H

#include <stdexcept>

/**
 * \brief Custom error class
 */
class Snake_Error : public std::runtime_error
{
public:
    Snake_Error ( const std::string& msg, const int line, const char* file )
            : runtime_error( msg ), _line ( line ), _file ( file )
    {}

    const int get_line () const;

    const char* get_file () const;

private:
    const int _line;
    const char* _file;
};

#endif //SNAKE_SNAKE_ERROR_H
