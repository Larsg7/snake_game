#ifndef ZOMBIE_LEVEL_H
#define ZOMBIE_LEVEL_H


#include <jaogll/sprite.h>
#include <vector>
#include <unordered_map>


class Level
{
public:
    void init ( std::string level_file, unsigned int spriteSize, JOGL::Color color = JOGL::Color ( 255, 255, 255, 255 ) );

    void generate_level ();

    std::vector<JOGL::Sprite>& getSprites ();

    void add_character_image ( char c, std::string filePath );

private:
    unsigned int _spriteSize;
    JOGL::Color _color;
    std::vector<std::vector<unsigned char>> _level;
    std::unordered_map<char, std::string> _assets;
    std::vector<JOGL::Sprite> _sprites;
};


#endif //ZOMBIE_LEVEL_H
