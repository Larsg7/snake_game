//
// Created by lars on 12/5/16.
//

#include "../inc/Snake_Error.h"

const int Snake_Error::get_line () const
{
    return _line;
}

const char* Snake_Error::get_file () const
{
    return _file;
}
