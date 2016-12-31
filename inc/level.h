#ifndef ZOMBIE_LEVEL_H
#define ZOMBIE_LEVEL_H


#include <jaogll/sprite.h>
#include <vector>

class Level
{
public:
    void init ();

    const std::vector<JOGL::Sprite>& getSprites () const;


private:
    std::vector<JOGL::Sprite> _sprites;

};


#endif //ZOMBIE_LEVEL_H
