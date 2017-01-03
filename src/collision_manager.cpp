
#include <map>
#include <algorithm>
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
        if ( agent->get_vel_unit() == glm::vec2 ( 0, 0 ) )
        {
            continue;
        }

        std::vector<std::pair<float,glm::vec2>> hits;
        glm::vec2 hitDir;

        for ( auto&& level : _level )
        {
            std::pair<float,glm::vec2> hit = get_hit_x_and_dir( agent, level.pos );

            if ( ( hit.second != glm::vec2 ( 0, 0 ) ) )
            {
                hits.push_back( hit );
            }
        }

        if ( hits.size() == 0 )
        {
            continue;
        }

        //printf( "%ld\n", hits.size() );

        std::sort( hits.begin(), hits.end(), [agent]( std::pair<float,glm::vec2> A, std::pair<float,glm::vec2> B ) {
            float x = agent->get_pos().x;
            return abs( x - A.first ) > abs ( x - B.first );
        } );

        hitDir = hits.begin()->second;

        glm::vec2 oldVel = agent->get_vel_unit();

        glm::vec2 newVel = oldVel - glm::dot( oldVel, hitDir ) * hitDir;
        printf( "%lf : %lf %lf : %lf %lf : %lf\n", oldVel.x, oldVel.y, hitDir.x, hitDir.y, newVel.x, newVel.y );
        if ( glm::length( newVel ) == 0 || hits.size() == 3 )
        {
            agent->set_vel_unit( glm::vec2 ( 0, 0 ) );
        }
        else
        {
            agent->set_vel_unit( glm::normalize( newVel) );
        }
    }
}

std::pair<float,glm::vec2> Collision_Manager::get_hit_x_and_dir ( Agent* agent, glm::vec4 rec ) const
{
    float radius = agent->get_radius();
    glm::vec2 oldPos = agent->get_pos();
    glm::vec2 newPos = oldPos + agent->get_vel_unit() * agent->get_speed();
    glm::vec2 vel = agent->get_vel_unit();

    float left = rec.x - radius;
    float right = rec.x + rec.z + radius;
    float bottom = rec.y - radius;
    float top = rec.y + rec.w + radius;

    // if newPos is not in the rectangle, return zero
    if ( ! (is_in_interval( newPos.x, left, right ) && is_in_interval( newPos.y, bottom, top )) )
    {
        return std::make_pair( 0, glm::vec2 ( 0, 0 ) );
    }

    /*
     * Idea:
     * |---|
     * |   |\
     * |---| \
     *       A
     * Find the point at which the trajectory of A given by f(x)=v.y/v.x * x + p.y - v.y/v.x * p.x
     * hits two of the sides (if it did not hit one, its no collision).
     * Get the one with the closest x value and you have your side which was hit.
     */
    float m = (vel.x == 0) ? vel.y * 100000 : vel.y / vel.x;
    float b = oldPos.y - m * oldPos.x;

    printf( "m: %f, b: %f", m, b );

    std::vector<std::pair<float,glm::vec2>> hits;

    float a;

    // bottom
    if ( is_in_interval( a = ((bottom - b) * 1 / m), left, right ) )
    {
        hits.push_back( std::make_pair( a, glm::vec2 ( 0, 1 ) ) );
    }
    // top
    if ( is_in_interval( a = ((top - b) * 1 / m), left, right ) )
    {
        hits.push_back( std::make_pair( a, glm::vec2 ( 0, -1 ) ) );
    }
    // left
    if ( is_in_interval( a = m * left + b, bottom, top ) )
    {
        hits.push_back( std::make_pair( left, glm::vec2 ( 1, 0 ) ) );
    }
    // right
    if ( is_in_interval( a = m * right + b, bottom, top ) )
    {
        hits.push_back( std::make_pair( right, glm::vec2 ( -1, 0 ) ) );
    }

    printf( "\n" );

    //<assert( hits.size() == 0 || hits.size() == 2 );

    if( hits.size() == 2 )
    {
        if ( abs( hits[0].first - oldPos.x ) < abs ( hits[1].first - oldPos.x ) )
        {
            return hits[0];
        }
        else
        {
            return hits[1];
        }
    }

    return std::make_pair( 0, glm::vec2 ( 0, 0 ) );
}

bool Collision_Manager::is_in_interval ( float x, float a, float b ) const
{
    return x > a && x < b;
}
