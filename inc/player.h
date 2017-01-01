
#ifndef ZOMBIE_PLAYER_H
#define ZOMBIE_PLAYER_H


#include <zombie_game/inc/agent.h>
#include <vector>
#include "bullet.h"

class Player : public Agent
{
public:
    virtual void init ( float speed, JOGL::Sprite sprite, const Bullet& bullet_sample );

    void shoot ( glm::vec2 pos );

    virtual void update ();

    const std::vector<Bullet>& get_bullets () const;

private:
    Bullet _bullet_sample;
    std::vector<Bullet> _bullets;
};


#endif //ZOMBIE_PLAYER_H
