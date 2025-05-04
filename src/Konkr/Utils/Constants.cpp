#include "Konkr/Utils/Constants.hpp"

#include "Engine/Utils/Logs.hpp"

const std::string& sprite_names::from_sprite_type(const SpriteType type)
{
    switch (type)
    {
    case SpriteType::Tile0:
        return tile0;
    case SpriteType::Tile1: 
        return tile1;
    case SpriteType::Tile1_Decoration1: 
        return tile1_decoration1;
    case SpriteType::Tile1_Decoration2: 
        return tile1_decoration2;
    case SpriteType::Tower1: 
        return tower1;
    case SpriteType::CityHall1: 
        return city_hall1;
    case SpriteType::Tile2: 
        return tile2;
    case SpriteType::Tower2:
        return tower2;
    case SpriteType::CityHall2:
        return city_hall2;
    case SpriteType::Tile3: 
        return tile3;
    case SpriteType::Tower3:
        return tower3;
    case SpriteType::CityHall3:
        return city_hall3;
    case SpriteType::Tile4:
        return tile4;
    case SpriteType::Tower4:
        return tower4;
    case SpriteType::CityHall4:
        return city_hall4;
    case SpriteType::Villager: 
        return villager;
    case SpriteType::Soldier: 
        return soldier;
    case SpriteType::Knight: 
        return knight;
    case SpriteType::Hero:
        return hero;
    case SpriteType::Highlighted:
        return hightlighted;
    case SpriteType::Bandit:
        return bandit;
    case SpriteType::None:
    default: 
        logs::error("SpriteType not found: {}", static_cast<int>(type));
        return tile0;
    }
}

const std::string& sprite_names::from_hex_direction(HexDirection direction)
{
    switch (direction)
    {
    case HexDirection::NorthWest:
        return fence_NW;
    case HexDirection::NorthEast:
        return fence_NE;
    case HexDirection::SouthEast:
        return fence_SE;
    case HexDirection::SouthWest:
        return fence_SW;
    case HexDirection::West:
        return fence_W;
    case HexDirection::East:
        return fence_E;
    default:
        logs::error("HexDirection not found: {}", static_cast<int>(direction));
        return fence_NW;
    }
}

float constants::get_sprite_decoration_factor(const SpriteType sprite)
{
    switch (sprite)
    {
    case SpriteType::CityHall1:
    case SpriteType::CityHall2:
    case SpriteType::CityHall3:
    case SpriteType::CityHall4:
    case SpriteType::Tower1:
    case SpriteType::Tower2:
    case SpriteType::Tower3:
    case SpriteType::Tower4:
        return building_sprite_factor;
    case SpriteType::Villager:
    case SpriteType::Soldier:
    case SpriteType::Knight:
    case SpriteType::Hero:
    case SpriteType::Bandit:
        return unit_sprite_factor;
    default:
        logs::error("Sprite type does not have a decoration factor {}", static_cast<int>(sprite));
        return 1.0f;
    }
}
