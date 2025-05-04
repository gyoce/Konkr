#include "Konkr/Hex/HexContainer.hpp"

#include <ranges>

HexTile::REF HexContainer::add_hex(const HexTile& hex)
{
    m_hex_map.emplace(hex.get_position(), hex);
    return std::ref(m_hex_map.at(hex.get_position()));
}

void HexContainer::remove_hex(const Vector3i& pos)
{
    m_hex_map.erase(pos);
}

std::optional<HexTile::REF> HexContainer::get_neighbor(const HexTile& from, HexDirection direction)
{
    const Vector3i neighbor_pos = from.get_position() + neighbor_directions[static_cast<std::size_t>(direction)];
    if (m_hex_map.contains(neighbor_pos))
        return std::ref(m_hex_map.at(neighbor_pos));
    return std::nullopt;
}

std::vector<HexTile::REF> HexContainer::get_player_hexes(const int player)
{
    return get_hexes_if([player](const HexTile& hex) { return hex.get_player() == player; });
}

std::vector<HexTile::REF> HexContainer::get_player_castles(const int player)
{
    return get_hexes_if([player](const HexTile& hex) { return hex.get_player() == player && hex.get_decoration() == HexEntity::Castle; });
}

std::vector<HexTile::REF> HexContainer::get_decoration_hexes(HexEntity decoration)
{
    return get_hexes_if([decoration](const HexTile& hex) { return hex.get_decoration() == decoration; });
}

std::vector<HexTile::REF> HexContainer::get_castles()
{
    return get_hexes_if([](const HexTile& hex) { return hex.get_decoration() == HexEntity::Castle; });
}

std::vector<Entity::SP> HexContainer::get_player_units_entities(const int player)
{
    std::vector<Entity::SP> units;
    for (const HexTile& hex : m_hex_map | std::views::values)
        if (hex.get_player() == player && hex.has_unit() && hex.get_decoration() != HexEntity::Bandit)
            units.push_back(hex.get_entity());
    return units;
}

std::vector<HexTile::REF> HexContainer::get_neighbors(const HexTile& from)
{
    return get_neighbors_if(from, [](const HexTile&) { return true; });
}

void HexContainer::clear()
{
    m_hex_map.clear();
}
