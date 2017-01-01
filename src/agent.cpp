#include "zombie_game/inc/agent.h"

void Agent::init ( float speed, JOGL::Sprite sprite )
{
    _pos.x = sprite.pos.x;
    _pos.y = sprite.pos.y;
    _speed = speed;
    _sprite = sprite;
}

void Agent::update ()
{
    _pos += _speed * _vel_unit;
    _sprite.pos.x = _pos.x;
    _sprite.pos.y = _pos.y;
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
    _pos.x = sprite.pos.x;
    _pos.y = sprite.pos.y;
}

void Agent::set_pos ( const glm::vec2& pos )
{
    _pos = pos;
    _sprite.pos.x = pos.x;
    _sprite.pos.y = pos.y;
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
