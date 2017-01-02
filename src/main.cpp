#include <iostream>
#include <jaogll/error.h>
#include <jaogll/logger.h>

#include "../inc/main_game.h"

JOGL::LogLevel JOGL::Logger::current_log_level = JOGL::LogLevel::LOG_DEBUG;

int main ()
{
    try
    {
        MainGame zombie ( 1200, 920 );

        zombie.run();
    }
    catch ( const JOGL::Jaogll_Error& e )
    {
        fprintf( stderr, "FATAL ERROR - on line %d in file '%s':\n%s\n"
                , e.get_line(), e.get_file(), e.what() );
        return 1;
    }
    catch ( ... )
    {
        fprintf( stderr, "There was an unknown error!" );
        return 1;
    }

    return 0;

}