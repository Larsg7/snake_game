#include "../inc/zombie.h"

void Zombie::follow_player ()
{
    _vel_unit = glm::normalize( _player->get_pos() - _pos );
}

void Zombie::set_player ( Player* _player )
{
    Zombie::_player = _player;
}
