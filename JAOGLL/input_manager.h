#ifndef SNAKE_INPUT_MANAGER_H
#define SNAKE_INPUT_MANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace JOGL
{
    /**
     * \brief Class to keep track of which key is pressed and where the mouse is.
     */
    class Input_Manager
    {
    public:
        Input_Manager ();

        void press_key ( unsigned int keyID );
        void release_key ( unsigned int keyID );

        void set_mouse_coords( float x, float y );

        const glm::vec2& get_mouse_coords () const;

        bool is_key_presses ( unsigned int keyID );

    private:
        std::unordered_map<unsigned int, bool> _keyMap;
        glm::vec2 _mouseCoords;
    };
}

#endif //SNAKE_INPUT_MANAGER_H