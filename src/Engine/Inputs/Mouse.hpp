#ifndef ENGINE_MOUSE_HPP
#define ENGINE_MOUSE_HPP

#include <cstdint>

#include "Engine/Math/Math.hpp"

class Mouse
{
public:
    Mouse() = delete;

    enum Button : std::uint8_t
    {
        NotRecognized,
        Left,
        Right,
        Middle
    };

    static bool is_button_down(Button button);
    static Vector2i get_position();
};

#endif // ENGINE_MOUSE_HPP