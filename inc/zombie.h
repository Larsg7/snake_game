#ifndef ZOMBIE_ZOMBIE_H
#define ZOMBIE_ZOMBIE_H


#include "agent.h"
#include "player.h"

class Zombie : public Agent
{
public:
    void follow_player ();

    void set_player ( Player* _player );

private:
    Player* _player;
};


#endif //ZOMBIE_ZOMBIE_H
