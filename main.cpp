#include <iostream>
#include "main_game.h"
#include "JAOGLL/error.h"

int main ()
{
    GameState game_state = GameState::PLAY;

    try
    {
        MainGame snake ( 600, 600 );

        JOGL::Sprite* s1 = new JOGL::Sprite();
        s1->init( 0.0, 0.0, 300, 300, "../media/PNG/CharacterRight_Standing.png" );

        JOGL::Sprite* s2 = new JOGL::Sprite();
        s2->init( 300, 300, 300, 300, "../media/PNG/CharacterLeft_Standing.png" );

        snake.add_sprite( s1 );
        snake.add_sprite( s2 );

        float x = 0;

        snake.run();
    }
    catch ( const JOGL::Jaogll_Error& e )
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