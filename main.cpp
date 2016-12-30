#include <iostream>
#include "JAOGLL/main_game.h"
#include "JAOGLL/jaogll_error.h"

int main ()
{
    try
    {
        MainGame snake ( 20, 20 );
        snake.run();
    }
    catch ( const Jaogll_Error& e )
    {
        fprintf( stderr, "FATAL ERROR - on line %d in file '%s':\n%s"
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