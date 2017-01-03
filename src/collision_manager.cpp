
#include "../inc/collision_manager.h"

void Collision_Manager::set_level ( const std::vector<JOGL::Sprite>& _level )
{
    Collision_Manager::_level = _level;
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
            if ( is_in_rectangle( agent->get_sprite().get_middle() + agent->get_vel_unit() * agent->get_speed()
                                  , level.pos, agent->get_radius() ) )
            {
                glm::vec2 hitDir = glm::vec2 ( 0, 0 );
                glm::vec2 oldVel = agent->get_vel_unit();
                glm::vec2 dir[4] = { glm::vec2( 0, 1 ), glm::vec2( 0, -1 ), glm::vec2( 1, 0 ), glm::vec2( -1, 0 ) };
                for ( int i = 0; i < 4; ++i )
                {
                    if ( glm::dot( oldVel, dir[i] ) >= 1 / sqrt( 2 ) - 0.0001f )
                    {
                        hitDir = dir[i];
                    }
                }

                glm::vec2 newVel = oldVel - glm::dot( oldVel, hitDir ) * hitDir;
                printf( "%lf : %lf %lf : %lf %lf : %lf\n", oldVel.x, oldVel.y, hitDir.x, hitDir.y, newVel.x, newVel.y );
                if ( glm::length( newVel ) == 0 )
                {
                    agent->set_vel_unit( glm::vec2 ( 0, 0 ) );
                }
                else
                {
                    agent->set_vel_unit( glm::normalize( newVel) );
                }
                //agent->set_pos( agent->get_pos() - 1.0f * hitDir );
                break;
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
