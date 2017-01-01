#ifndef ZOMBIE_LEVEL_H
#define ZOMBIE_LEVEL_H


#include <jaogll/sprite.h>
#include <vector>
#include <unordered_map>


class Level
{
public:
    /**
     * \brief Set variables and read level_file into _level.
     * \param level_file File containing the level information.
     * \param spriteSize Size of one sprite (length of one side)
     * \param color      Color to use for the sprites (defaults to white)
     */
    void init ( std::string level_file, unsigned int spriteSize, JOGL::Color color = JOGL::Color ( 255, 255, 255, 255 ) );

    /**
     * \brief Populates _sprites according to the characters in _level and _assets.
     */
    void generate_level ();

    const std::vector<JOGL::Sprite>& getSprites () const;

    /**
     * \brief Add a char - path-to-image pair to _assets. Will be used to decode the level file.
     * \param c        Character key.
     * \param filePath Path to the image
     */
    void add_character_image ( char c, std::string filePath );

private:
    unsigned int _spriteSize;
    JOGL::Color _color;
    std::vector<std::vector<unsigned char>> _level;
    std::unordered_map<char, std::string> _assets;
    std::vector<JOGL::Sprite> _sprites;
};


#endif //ZOMBIE_LEVEL_H
