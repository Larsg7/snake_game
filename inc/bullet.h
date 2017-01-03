//
// Created by lars on 1/1/17.
//

#ifndef ZOMBIE_BULLET_H
#define ZOMBIE_BULLET_H


#include "agent.h"

class Bullet : public Agent
{
public:
    Bullet () : _liveTime ( 0 ), _alive ( true )
    {}

    virtual void update ();

    bool is_alive () const;

    static float maxLiveTime;

private:
    float _liveTime;
    bool _alive;
};


#endif //ZOMBIE_BULLET_H
