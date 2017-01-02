#include "../inc/bullet.h"

void Bullet::update ()
{
    Agent::update();
    _alive = _liveTime++ <= maxLiveTime;
}

bool Bullet::is_alive () const
{
    return _alive;
}
