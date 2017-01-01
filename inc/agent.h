
#ifndef ZOMBIE_AGENT_H
#define ZOMBIE_AGENT_H


#include <jaogll/sprite.h>

class Agent
{
public:
    virtual void init ( float speed, JOGL::Sprite sprite );

    virtual void update ();

    const JOGL::Sprite& get_sprite () const;

    const glm::vec2& get_pos () const;

    const glm::vec2& get_vel_unit () const;

    void set_sprite ( const JOGL::Sprite& sprite );

    void set_pos ( const glm::vec2& pos );

    void set_vel_unit ( const glm::vec2& vel );

    void set_speed ( float speed );

protected:
    JOGL::Sprite _sprite;
    glm::vec2 _pos;
    glm::vec2 _vel_unit;
    float _speed;
};


#endif //ZOMBIE_AGENT_H
