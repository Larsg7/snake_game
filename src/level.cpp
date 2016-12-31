#include "zombie_game/inc/level.h"
#include <jaogll/sprite.h>

void Level::init ()
{
    const int spriteSize = 50;

    const std::string image_wall = "../media/bricksx64.png";
    const std::string image_floor = "../media/Green_3_gridbox.png";
    const JOGL::Color color ( 255, 255, 255, 255 );

    const int level_width = 20;
    const int level_height = 20;

    for ( int i = - level_height / 2; i < level_height / 2; ++i )
    {
        for ( int j = - level_width / 2; j < level_width / 2; ++j )
        {
            _sprites.emplace_back( i * spriteSize, j * spriteSize, spriteSize, spriteSize, color, image_floor );
        }
    }

    for ( float k = -1 * (level_width / 2 + 1); k < level_width / 2 + 1; ++k )
    {
        _sprites.emplace_back( k * spriteSize, 0, spriteSize, spriteSize, color, image_wall );
    }
}

const std::vector<JOGL::Sprite>& Level::getSprites () const
{
    return _sprites;
}
