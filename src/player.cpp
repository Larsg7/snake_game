
#include "zombie_game/inc/player.h"

void Player::init ( float speed, JOGL::Sprite sprite, const Bullet& bullet_sample )
{
    Agent::init( speed, sprite );
    _bullet_sample = bullet_sample;
}

void Player::shoot ( glm::vec2 pos )
{
    _bullets.emplace_back( _bullet_sample );
    _bullets.back().set_pos( _pos );
    _bullets.back().set_vel_unit( glm::normalize( pos - _pos ) );
}

void Player::update ()
{
    Agent::update();
    for ( auto it = _bullets.begin(); it != _bullets.end() && _bullets.size() > 0; ++it )
    {
        printf( "%d\n", _bullets.size() );
        it->update();
        if ( ! it->is_alive() )
        {
            _bullets.erase( it );
        }
    }
}

const std::vector<Bullet>& Player::get_bullets () const
{
    return _bullets;
}
