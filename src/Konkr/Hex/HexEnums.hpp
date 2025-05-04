#ifndef KONKR_HEX_ENUMS_HPP
#define KONKR_HEX_ENUMS_HPP

#include <cstdint>
#include <array>

enum class HexType : std::uint8_t
{
    Unknown,
    Territory,
    Decoration,
};

enum class HexEntity : std::uint8_t
{
    None,
    Bandit,
    Villager,
    Soldier,
    Knight,
    Hero,
    Castle,
    Tower
};

enum class HexDirection : std::uint8_t
{
    East,
    NorthEast,
    NorthWest,
    West,
    SouthWest,
    SouthEast
};

inline constexpr std::array AllHexDirections = 
{
    HexDirection::East,
    HexDirection::NorthEast,
    HexDirection::NorthWest,
    HexDirection::West,
    HexDirection::SouthWest,
    HexDirection::SouthEast
};

#endif // KONKR_HEX_ENUMS_HPP