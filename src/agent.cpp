#include "../inc/agent.h"

void Agent::init ( float speed, JOGL::Sprite sprite, float radius, AgentType type )
{
    _pos = sprite.get_middle();
    _speed = speed;
    _sprite = sprite;
    _radius = radius;
    _type = type;
}

void Agent::update ()
{
    _pos += _speed * _vel_unit;
    _sprite.set_middle( _pos );
}

const JOGL::Sprite& Agent::get_sprite () const
{
    return _sprite;
}

const glm::vec2& Agent::get_pos () const
{
    return _pos;
}

void Agent::set_sprite ( const JOGL::Sprite& sprite )
{
    _sprite = sprite;
    _pos = sprite.get_middle();
}

void Agent::set_pos ( const glm::vec2& pos )
{
    _pos = pos;
    _sprite.set_middle( pos );
}

void Agent::set_vel_unit ( const glm::vec2& vel )
{
    _vel_unit = vel;
}

void Agent::set_speed ( float speed )
{
    _speed = speed;
}

const glm::vec2& Agent::get_vel_unit () const
{
    return _vel_unit;
}

float Agent::get_radius () const
{
    return _radius;
}
