
#include "../inc/player.h"

void Player::init ( float speed, JOGL::Sprite sprite, const Bullet& bullet_sample, float radius )
{
    Agent::init( speed, sprite, 0, AgentType::PLAYER );
    _bullet_sample = bullet_sample;
    _radius = radius;
}

void Player::shoot ( glm::vec2 pos )
{
    Bullet* newBullet = new Bullet;
    *newBullet = _bullet_sample;
    _bullets.emplace_back( newBullet );
    _bullets.back()->set_pos( _pos );
    _bullets.back()->set_vel_unit( glm::normalize( pos - _pos ) );
}

void Player::update ()
{
    Agent::update();
    for ( auto it = _bullets.begin(); it != _bullets.end() && _bullets.size() > 0; ++it )
    {
        (*it)->update();
        if ( ! (*it)->is_alive() )
        {
            _bullets.erase( it );
        }
    }
}

const std::vector<Bullet*>& Player::get_bullets () const
{
    return _bullets;
}
