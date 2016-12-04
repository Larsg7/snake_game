#include <iostream>
#include "inc/snake_game.h"
#include "inc/Snake_Error.h"

int main ()
{
    try
    {
        Snake snake ( 20, 20 );
        snake.run();
    }
    catch ( const Snake_Error& e )
    {
        printf( "There was an error: %s", e.what() );
        return 1;
    }
    catch ( ... )
    {
        printf( "There was an unknown error!" );
        return 1;
    }

    return 0;
}