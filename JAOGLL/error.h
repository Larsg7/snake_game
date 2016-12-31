#ifndef SNAKE_SNAKE_ERROR_H
#define SNAKE_SNAKE_ERROR_H

#include <stdexcept>

namespace JOGL
{
#define JOAGLL_ERROR( m ) (JOGL::Jaogll_Error((m), __LINE__, __FILE__))

    /**
     * \brief Custom error class.
     * Reports line number and file.
     */
    class Jaogll_Error : public std::runtime_error
    {
    public:
        Jaogll_Error ( const std::string& msg, const int line, const char* file )
                : runtime_error( msg ), _line( line ), _file( file )
        {}

        const int get_line () const;

        const char* get_file () const;

    private:
        const int _line;
        const char* _file;
    };
}

#endif //SNAKE_SNAKE_ERROR_H
