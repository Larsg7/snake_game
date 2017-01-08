
#include <algorithm>
#include "../inc/agent_manager.h"
#include "../inc/main_game.h"


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
    newBullet->set_pos( _player->get_pos() + 2.0f * _player->get_radius() * glm::normalize( pos - _player->get_pos() ) );
    newBullet->set_vel_unit( glm::normalize( pos - _player->get_pos() ) );
    _agents.push_back( newBullet );
}

void Agent_Manager::agent_collided ( Agent* A, Agent* B )
{
    //printf( "%d : %d\n", A->get_type(), B->get_type() );
    switch ( A->get_type() )
    {
        case AgentType::ZOMBIE:
            switch ( B->get_type() )
            {
                case AgentType::PLAYER:
                    MainGame::set_gameState( GameState::GAMEOVER );
                    break;
                case AgentType::HUMAN:
                    _agents.emplace_back( new Zombie );
                    _agents.back()->init( B->get_speed(), A->get_sprite(), B->get_radius(), AgentType::ZOMBIE );
                    _agents.back()->set_pos( B->get_pos() );
                    erase_agent( B );
                    break;
            }
            break;
        case AgentType::BULLET:
            erase_agent( A );
            switch ( B->get_type() )
            {
                case AgentType::ZOMBIE:
                case AgentType::HUMAN:
                    erase_agent( B );
                    break;
            }
            break;
    }
}

void Agent_Manager::ai ()
{
    for ( auto&& agent : _agents )
    {
        switch ( agent->get_type() )
        {
            case AgentType::ZOMBIE:
                ai_zombie( dynamic_cast<Zombie*>(agent) );
                break;
            case AgentType::HUMAN:
                ai_human( dynamic_cast<Human*>(agent) );
                break;
        }
    }
}

void Agent_Manager::ai_zombie ( Zombie* zombie )
{
    zombie->set_vel_unit( glm::normalize( _player->get_pos() - zombie->get_pos() ) );
}

void Agent_Manager::ai_human ( Human* human )
{

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
                update_human( dynamic_cast<Human*>(agent) );
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

void Agent_Manager::update_human ( Human* human )
{
    human->update();
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

void Agent_Manager::erase_agent ( Agent* agent )
{
    //TODO use shared pointer!
    auto it = std::find( _agents.begin(), _agents.end(), agent );
    if ( it != _agents.end() )
    {
        _agents.erase( it );
    }
}
