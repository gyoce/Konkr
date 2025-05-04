#ifndef ENGINE_GUI_ENUMS_HPP
#define ENGINE_GUI_ENUMS_HPP

#include <cstdint>

enum class Horizontal : std::uint8_t
{
    Left,
    Center,
    Right
};

enum class Vertical : std::uint8_t
{
    Top,
    Center,
    Bottom
};

#endif // ENGINE_GUI_ENUMS_HPP