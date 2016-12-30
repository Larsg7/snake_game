//
// Created by lars on 12/5/16.
//

#include "../error.h"

const int JOGL::Jaogll_Error::get_line () const
{
    return _line;
}

const char* JOGL::Jaogll_Error::get_file () const
{
    return _file;
}
