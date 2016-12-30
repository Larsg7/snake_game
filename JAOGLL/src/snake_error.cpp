//
// Created by lars on 12/5/16.
//

#include "../jaogll_error.h"

const int Jaogll_Error::get_line () const
{
    return _line;
}

const char* Jaogll_Error::get_file () const
{
    return _file;
}
