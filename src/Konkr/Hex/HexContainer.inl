#include <ranges>

template<std::predicate<HexTile&> Pred>
std::vector<HexTile::REF> HexContainer::get_neighbors_if(const HexTile& from, Pred pred)
{
    std::vector<HexTile::REF> neighbors;
    for (const Vector3i& direction : neighbor_directions)
    {
        const Vector3i neighbor_pos = from.get_position() + direction;
        if (m_hex_map.contains(neighbor_pos))
        {
            HexTile& neighbor = m_hex_map.at(neighbor_pos);
            if (pred(neighbor))
                neighbors.push_back(std::ref(neighbor));
        }
    }
    return neighbors;
}

template<std::predicate<HexTile&> Pred>
std::vector<HexTile::REF> HexContainer::get_hexes_if(Pred pred)
{
    std::vector<HexTile::REF> hexes;
    for (HexTile& hex : m_hex_map | std::views::values)
        if (pred(hex))
            hexes.push_back(std::ref(hex));
    return hexes;
}

template <std::predicate<HexTile&> Pred>
int HexContainer::count_if(Pred pred) const
{
    int count = 0;
    for (const HexTile& hex : m_hex_map | std::views::values)
        if (pred(hex))
            ++count;
    return count;
}
