#include <iostream>
#include "../inc/snake_game.h"
#include "../inc/Snake_Error.h"

int main ()
{
    try
    {
        Snake snake ( 20, 20 );
        snake.run();
    }
    catch ( const Snake_Error& e )
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