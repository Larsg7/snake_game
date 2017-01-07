
#include <map>
#include <algorithm>
#include "../inc/collision_manager.h"
#include "../inc/bullet.h"

void Collision_Manager::set_level ( const std::vector<JOGL::Sprite>& _level )
{
    Collision_Manager::_level = _level;
}

void Collision_Manager::set_agents ( const std::vector<Agent*>& _agents )
{
    Collision_Manager::_agents = _agents;
}

Agent* Collision_Manager::collide ( Agent* agent )
{
    // if the agent is not moving, continue
    if ( agent->get_vel_unit() == glm::vec2 ( 0, 0 ) )
    {
        return nullptr;
    }

    Agent* c_agent = nullptr;

    std::vector<std::pair<glm::vec2,glm::vec2>> hits;
    glm::vec2 hitDir;

    for ( auto&& level : _level )
    {
        std::pair<glm::vec2,glm::vec2> hit = get_hit_pos_and_dir( agent, level.pos );

        if ( ( hit.second != glm::vec2 ( 0, 0 ) ) )
        {
            hits.push_back( hit );
        }
    }

    for ( auto&& a : _agents )
    {
        glm::vec2 dist = a->get_pos() - agent->get_pos();
        if ( a == agent || (glm::length( dist ) > (a->get_radius() + agent->get_radius())) )
        {
            continue;
        }

        agent->set_pos( agent->get_pos()
                        - glm::normalize( dist ) * ( (a->get_radius() + agent->get_radius()) -  glm::length( dist )) );
        c_agent = a;
        hits.emplace_back();
    }

    // if there were no hits, continue
    if ( hits.size() == 0 )
    {
        return nullptr;
    }

    // sort hits so that the nearest hit is closest
    std::sort( hits.begin(), hits.end(), [agent]( std::pair<glm::vec2,glm::vec2> A, std::pair<glm::vec2,glm::vec2> B ) {
        glm::vec2 oldPos = agent->get_pos();
        return glm::length( oldPos - A.first ) < glm::length( oldPos - B.first );
    } );

    // use closest hit as hitDir
    hitDir = hits.begin()->second;

    glm::vec2 oldVel = agent->get_vel_unit();

    // should bullets bounce?
    float bounce = (agent->get_type() == AgentType::BULLET) ? 1.9f : 1.0f;

    glm::vec2 newVel = oldVel - glm::dot( oldVel, hitDir ) * hitDir * bounce;
    //printf( "%lf : %lf %lf : %lf %lf : %lf\n", oldVel.x, oldVel.y, hitDir.x, hitDir.y, newVel.x, newVel.y );
    if ( glm::length( newVel ) == 0 || hits.size() == 3 ) // last one to fix the corners
    {
        agent->set_vel_unit( glm::vec2 ( 0, 0 ) );
    }
    else
    {
        agent->set_vel_unit( newVel );
    }

    return c_agent;
}

std::pair<glm::vec2,glm::vec2> Collision_Manager::get_hit_pos_and_dir ( Agent* agent, glm::vec4 rec ) const
{
    float radius = agent->get_radius();
    glm::vec2 oldPos = agent->get_pos();
    glm::vec2 newPos = oldPos + agent->get_vel_unit() * agent->get_speed();
    glm::vec2 vel = agent->get_vel_unit();

    // rectangle with radius
    float left = rec.x - radius;
    float right = rec.x + rec.z + radius;
    float bottom = rec.y - radius;
    float top = rec.y + rec.w + radius;

    // if newPos is not in the rectangle, return zero
    if ( ! (is_in_interval( newPos.x, left, right ) && is_in_interval( newPos.y, bottom, top )) )
    {
        return std::make_pair( glm::vec2 ( 0, 0 ), glm::vec2 ( 0, 0 ) );
    }

    /*
     * Idea:
     * |---|
     * |   |\
     * |---| \
     *       A
     * Find the point at which the trajectory of A given by f(x)=v.y/v.x * x + p.y - v.y/v.x * p.x
     * hits two of the sides (if it did not hit one, it's no collision).
     * Get the one with the closest distance and you have your side which was hit.
     */
    float m = (vel.x == 0) ? vel.y * 100000 : vel.y / vel.x;
    float b = oldPos.y - m * oldPos.x;

    std::vector<std::pair<glm::vec2,glm::vec2>> hits;

    float a;

    // bottom
    if ( is_in_interval( a = ((bottom - b) * 1 / m), left, right ) )
    {
        hits.push_back( std::make_pair( glm::vec2 ( a, bottom ), glm::vec2 ( 0, 1 ) ) );
    }
    // top
    if ( is_in_interval( a = ((top - b) * 1 / m), left, right ) )
    {
        hits.push_back( std::make_pair( glm::vec2 ( a, top), glm::vec2 ( 0, -1 ) ) );
    }
    // left
    if ( is_in_interval( a = m * left + b, bottom, top ) )
    {
        hits.push_back( std::make_pair( glm::vec2 ( left, a ), glm::vec2 ( 1, 0 ) ) );
    }
    // right
    if ( is_in_interval( a = m * right + b, bottom, top ) )
    {
        hits.push_back( std::make_pair( glm::vec2 ( right, a ), glm::vec2 ( -1, 0 ) ) );
    }

    //<assert( hits.size() == 0 || hits.size() == 2 );

    if ( hits.size() == 0 )
    {
        return std::make_pair( glm::vec2 ( 0, 0 ), glm::vec2 ( 0, 0 ) );
    }
    // sort hits so that nearest is first
    std::sort( hits.begin(), hits.end(), [oldPos]( std::pair<glm::vec2,glm::vec2> A, std::pair<glm::vec2,glm::vec2> B ) {
        return glm::length( oldPos - A.first ) < glm::length( oldPos - B.first );
    } );

    return *(hits.begin());
}

bool Collision_Manager::is_in_interval ( float x, float a, float b ) const
{
    return x > a && x < b;
}
