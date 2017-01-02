
#include "../inc/collision_manager.h"

void Collision_Manager::set_level ( const std::vector<JOGL::Sprite>& _level )
{
    Collision_Manager::_level = _level;
    printf( "%ld", _level.size() );
}

void Collision_Manager::set_agents ( const std::vector<Agent*>& _agents )
{
    Collision_Manager::_agents = _agents;
}

void Collision_Manager::update ()
{
    for ( auto&& agent : _agents )
    {
        for ( auto&& level : _level )
        {
            if ( is_in_rectangle( agent->get_sprite().get_middle(), level.pos, agent->get_radius() ) )
            {
                glm::vec2 hitDir = glm::normalize( level.get_middle() - agent->get_sprite().get_middle() );
                glm::vec2 oldVel = agent->get_vel_unit();
                agent->set_vel_unit( oldVel - glm::dot( oldVel, hitDir ) * hitDir - 1.0f * hitDir );
                //agent->set_pos( agent->get_pos() - 1.0f * hitDir );
            }
        }
    }
}

bool Collision_Manager::is_in_rectangle ( glm::vec2 pos, glm::vec4 rec, float radius ) const
{
    float left = rec.x - radius;
    float right = rec.x + rec.z + radius;
    float bottom = rec.y - radius;
    float top = rec.y + rec.w + radius;
    return    pos.x > left   && pos.x < right
           && pos.y > bottom && pos.y < top;
}
