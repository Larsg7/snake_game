#include "../inc/level.h"
#include <jaogll/iomanager.h>
#include <jaogll/logger.h>

void Level::init ( std::string level_file, unsigned int spriteSize, JOGL::Color color )
{
    _spriteSize = spriteSize;
    _color = color;

    JOGL::IOManager::read_file_to_buffer_line( _level, level_file );
}

const std::vector<JOGL::Sprite>& Level::getSprites () const
{
    return _sprites;
}

void Level::add_character_image ( char c, std::string filePath )
{
    _assets.insert( std::make_pair( c, filePath ) );
}

void Level::generate_level ()
{
    for ( int i = 0; i < _level.size(); ++i )
    {
        for ( int j = 0; j < _level[i].size(); ++j )
        {
            auto mit = _assets.find( _level[i][j] );
            if ( mit != _assets.end() )
            {
                _sprites.emplace_back( j * _spriteSize, i * _spriteSize, _spriteSize, _spriteSize, _color, mit->second, 0 );
            }
            else
            {
                JOGL::Logger::log( "Undefined character " + std::string (1, _level[i][j] ) + " in level file!", JOGL::LogLevel::LOG_ERROR );
            }
        }
    }
}
