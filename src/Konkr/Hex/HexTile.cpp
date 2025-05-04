#include "Konkr/Hex/HexTile.hpp"

#include <cassert>

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"

HexTile::HexTile(const int q, const int r, const int s, const HexType type, Entity::SP entity, const int player)
    : m_position(q, r, s), m_type(type), m_player(player), m_entity(std::move(entity))
{
    assert(q + r + s == 0 && "Coordinates q+r+s must be equal to 0.");
    update_sprites();
}

bool HexTile::has_movable_decoration() const
{
    return has_entity() && m_entity->is_movable();
}

const Texture::SP& HexTile::get_sprite_tile() const
{
    return ResourceManager::get_sprite(sprite_names::from_sprite_type(m_sprite_tile));
}

const Texture::SP& HexTile::get_sprite_decoration() const
{
    return ResourceManager::get_sprite(sprite_names::from_sprite_type(m_sprite_decoration));
}

std::vector<Texture::SP> HexTile::get_fence_sprites() const
{
    std::vector<Texture::SP> fence_sprites{};
    fence_sprites.reserve(m_fences.count());
    for (size_t i = 0; i < m_fences.size(); ++i)
        if (m_fences[i])
            fence_sprites.push_back(ResourceManager::get_sprite(sprite_names::from_hex_direction(static_cast<HexDirection>(i))));
    return fence_sprites;
}

bool HexTile::has_foreground() const
{
    return has_entity() && m_entity->get_decoration() != HexEntity::None && m_sprite_decoration != SpriteType::None && !disable_decoration;
}

bool HexTile::has_building() const
{
    return has_entity() && m_entity->is_building();
}

bool HexTile::has_unit() const
{
    return has_entity() && !m_entity->is_building();
}

int HexTile::distance(const HexTile& from, const HexTile& to)
{
    return std::abs(from.q() - to.q()) + std::abs(from.r() - to.r()) + std::abs(from.s() - to.s());
}

HexEntity HexTile::get_decoration() const
{
    return has_entity() ? m_entity->get_decoration() : HexEntity::None;
}

void HexTile::set_entity(Entity::SP entity)
{
    m_entity = std::move(entity);
    update_sprites();
}

void HexTile::set_type(const HexType type)
{
    m_type = type;
    update_sprites();
}

void HexTile::set_player(const int player)
{
    m_player = player;
    update_sprites();
}

void HexTile::set_fence(const HexDirection direction, const bool value)
{
    m_fences.set(static_cast<size_t>(direction), value);
}

void HexTile::remove_fences()
{
    m_fences.reset();
}

bool HexTile::operator==(const HexTile& other) const
{
    return m_position == other.m_position;
}

void HexTile::update_sprites()
{
    switch (m_type)
    {
    case HexType::Decoration:
        m_sprite_tile = SpriteType::Tile1_Decoration2;
        break;
    case HexType::Territory:
        switch (m_player)
        {
        case 1:
            m_sprite_tile = SpriteType::Tile1;
            break;
        case 2:
            m_sprite_tile = SpriteType::Tile2;
            break;
        case 3:
            m_sprite_tile = SpriteType::Tile3;
            break;
        case 4:
            m_sprite_tile = SpriteType::Tile4;
            break;
        default:
            m_sprite_tile = SpriteType::Tile0;
            break;
        }
        break;
    }

    switch (get_decoration())
    {
    case HexEntity::Tower:
        switch (m_player)
        {
        case 1:
            m_sprite_decoration = SpriteType::Tower1;
            break;
        case 2:
            m_sprite_decoration = SpriteType::Tower2;
            break;
        case 3:
            m_sprite_decoration = SpriteType::Tower3;
            break;
        case 4:
            m_sprite_decoration = SpriteType::Tower4;
            break;
        }
        break;
    case HexEntity::Castle:
        switch (m_player)
        {
        case 1:
            m_sprite_decoration = SpriteType::CityHall1;
            break;
        case 2:
            m_sprite_decoration = SpriteType::CityHall2;
            break;
        case 3:
            m_sprite_decoration = SpriteType::CityHall3;
            break;
        case 4:
            m_sprite_decoration = SpriteType::CityHall4;
            break;
        }
        break;
    case HexEntity::Villager:
        m_sprite_decoration = SpriteType::Villager;
        break;
    case HexEntity::Soldier:
        m_sprite_decoration = SpriteType::Soldier;
        break;
    case HexEntity::Knight:
        m_sprite_decoration = SpriteType::Knight;
        break;
    case HexEntity::Hero:
        m_sprite_decoration = SpriteType::Hero;
        break;
    case HexEntity::Bandit:
        m_sprite_decoration = SpriteType::Bandit;
        break;
    default:
        m_sprite_decoration = SpriteType::None;
        break;
    }
}