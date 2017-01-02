
#ifndef ZOMBIE_COLLISION_MANAGER_H
#define ZOMBIE_COLLISION_MANAGER_H


#include <vector>
#include <jaogll/sprite.h>
#include "agent.h"

class Collision_Manager
{
public:
    void set_level ( const std::vector<JOGL::Sprite>& _level );

    void set_agents ( const std::vector<Agent*>& _agents );

    void update ();

private:
    std::vector<JOGL::Sprite> _level;
    std::vector<Agent*> _agents;

    bool is_in_rectangle ( glm::vec2 pos, glm::vec4 rec, float radius ) const;
};


#endif //ZOMBIE_COLLISION_MANAGER_H
