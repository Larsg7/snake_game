
#include <algorithm>
#include "../inc/agent_manager.h"


void Agent_Manager::init ( Player* player )
{
    _player = player;
    _agents.push_back( _player );
}

void Agent_Manager::add_agent ( Agent* agent )
{
    _agents.push_back( agent );
}

void Agent_Manager::add_agent ( std::vector<Agent*> v )
{
    std::copy( v.begin(), v.end(), std::back_inserter( _agents ) );
}

void Agent_Manager::add_bullet_sample ( Bullet bullet_sample )
{
    _bullet_sample = bullet_sample;
}

void Agent_Manager::player_shoot ( glm::vec2 pos )
{
    Bullet* newBullet = new Bullet;
    *newBullet = _bullet_sample;
    newBullet->set_pos( _player->get_pos() + _player->get_radius() * glm::normalize( pos - _player->get_pos() ) );
    newBullet->set_vel_unit( glm::normalize( pos - _player->get_pos() ) );
    _agents.push_back( newBullet );
}

void Agent_Manager::agent_collided ( Agent* A, Agent* B )
{
    printf( "%d : %d\n", A->get_type(), B->get_type() );
    switch ( A->get_type() )
    {
        case AgentType::ZOMBIE:
            switch ( B->get_type() )
            {
                case AgentType::BULLET:
                    _agents.erase( std::find( _agents.begin(), _agents.end(), A ) );
                    _agents.erase( std::find( _agents.begin(), _agents.end(), B ) );
                    break;
            }
            break;
        case AgentType::BULLET:
            switch ( B->get_type() )
            {
                case AgentType::ZOMBIE:
                    _agents.erase( std::find( _agents.begin(), _agents.end(), A ) );
                    _agents.erase( std::find( _agents.begin(), _agents.end(), B ) );
                    break;
            }
            break;
    }
}

void Agent_Manager::update ()
{
    update_player();
    for ( auto&& agent : _agents )
    {
        switch ( agent->get_type() )
        {
            case AgentType::ZOMBIE:
                update_zombie( dynamic_cast<Zombie*>(agent) );
                break;
            case AgentType::HUMAN:
                update_human( agent );
                break;
            case AgentType::BULLET:
                update_bullet( dynamic_cast<Bullet*>(agent) );
                break;
        }
    }
}

void Agent_Manager::update_zombie ( Zombie* zombie )
{
    zombie->update();
}

void Agent_Manager::update_human ( Agent* human )
{

}

void Agent_Manager::update_bullet ( Bullet* bullet )
{
    bullet->update();
    if ( ! bullet->is_alive() )
    {
        _agents.erase( std::find( _agents.begin(), _agents.end(), dynamic_cast<Agent*>(bullet) ) );
    }
}

void Agent_Manager::update_player ()
{
    _player->update();
}

const std::vector<Agent*>& Agent_Manager::get_agents () const
{
    return _agents;
}
