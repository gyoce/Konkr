#ifndef ENGINE_COLOR_HPP
#define ENGINE_COLOR_HPP

#include <cstdint>

class Color
{
public:
    constexpr Color() = default;
    constexpr Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255) : r(r), g(g), b(b), a(a) {}

    constexpr bool operator==(const Color& other) const = default;

    uint8_t r{ 0 };
    uint8_t g{ 0 };
    uint8_t b{ 0 };
    uint8_t a{ 255 };

    static const Color None;
    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Orange;
    static const Color Purple;
    static const Color Pink;
};

// inline here is mandatory or VS2022 will not compile
inline constexpr Color Color::None{ 0, 0, 0, 0 };
inline constexpr Color Color::White { 255, 255, 255, 255 };
inline constexpr Color Color::Black { 0, 0, 0, 255 };
inline constexpr Color Color::Red{ 255, 0, 0, 255 };
inline constexpr Color Color::Green{ 0, 255, 0, 255 };
inline constexpr Color Color::Blue{ 0, 0, 255, 255 };
inline constexpr Color Color::Yellow{ 255, 255, 0, 255 };
inline constexpr Color Color::Magenta{ 255, 0, 255, 255 };
inline constexpr Color Color::Cyan{ 0, 255, 255, 255 };
inline constexpr Color Color::Orange{ 255, 165, 0, 255 };
inline constexpr Color Color::Purple{ 128, 0, 128, 255 };
inline constexpr Color Color::Pink{ 255, 192, 203, 255 };

#endif // ENGINE_COLOR_HPP