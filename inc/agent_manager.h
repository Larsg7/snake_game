
#ifndef ZOMBIE_AGENT_MANAGER_H
#define ZOMBIE_AGENT_MANAGER_H


#include <vector>
#include "agent.h"
#include "player.h"
#include "zombie.h"
#include "human.h"

class Agent_Manager
{
public:
    void init ( Player* player );

    void add_agent ( Agent* agent );

    void add_agent ( std::vector<Agent*> v );

    void player_shoot ( glm::vec2 pos );

    void add_bullet_sample ( Bullet bullet_sample );

    void agent_collided ( Agent* A, Agent* B );

    const std::vector<Agent*>& get_agents () const;

    void ai ();

    void update ();

private:
    void ai_zombie ( Zombie* zombie );
    void ai_human ( Human* human );

    void update_zombie ( Zombie* zombie );
    void update_human ( Human* human );
    void update_bullet ( Bullet* bullet );
    void update_player ();

    void erase_agent ( Agent* agent );

    std::vector<Agent*> _agents;
    Player* _player;

    Bullet _bullet_sample;
};


#endif //ZOMBIE_AGENT_MANAGER_H