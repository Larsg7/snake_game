//
// Created by lars on 1/1/17.
//

#include "zombie_game/inc/bullet.h"

void Bullet::update ()
{
    Agent::update();
    _alive = _liveTime++ <= maxLiveTime;
}

bool Bullet::is_alive () const
{
    return _alive;
}
