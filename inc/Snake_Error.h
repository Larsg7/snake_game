#ifndef SNAKE_SNAKE_ERROR_H
#define SNAKE_SNAKE_ERROR_H

#include <stdexcept>

class Snake_Error : public std::runtime_error
{
public:
    Snake_Error ( const std::string& msg )
            : runtime_error( msg )
    {}
};

#endif //SNAKE_SNAKE_ERROR_H
