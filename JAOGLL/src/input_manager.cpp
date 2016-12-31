
#include "../input_manager.h"

JOGL::Input_Manager::Input_Manager ()
        : _mouseCoords( 0, 0 )
{}

void JOGL::Input_Manager::press_key ( unsigned int keyID )
{
    _keyMap[keyID] = true;
}

void JOGL::Input_Manager::release_key ( unsigned int keyID )
{
    _keyMap[keyID] = false;
}

void JOGL::Input_Manager::set_mouse_coords ( float x, float y )
{
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool JOGL::Input_Manager::is_key_presses ( unsigned int keyID )
{
    if ( _keyMap.find( keyID ) != _keyMap.end() )
    {
        return _keyMap[keyID];
    }
    return false;
}

const glm::vec2& JOGL::Input_Manager::get_mouse_coords () const
{
    return _mouseCoords;
}
