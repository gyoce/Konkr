#ifndef KONKR_HEX_CONTAINER_HPP
#define KONKR_HEX_CONTAINER_HPP

#include "Konkr/Hex/HexTile.hpp"

#include <map>
#include <array>
#include <vector>
#include <optional>
#include <concepts>

class HexContainer
{
private:
    struct Comparator
    {
        bool operator()(const Vector3i& a, const Vector3i& b) const
        {
            if (a.y != b.y)
                return a.y < b.y;
            return a.x < b.x;
        }
    };

    std::map<Vector3i, HexTile, Comparator> m_hex_map;

public:
    HexContainer() = default;

    HexTile::REF add_hex(const HexTile& hex);
    void remove_hex(const Vector3i& pos);
    std::optional<HexTile::REF> get_neighbor(const HexTile& from, HexDirection direction);
    std::vector<HexTile::REF> get_neighbors(const HexTile& from);
    std::vector<HexTile::REF> get_player_hexes(int player);
    std::vector<HexTile::REF> get_player_castles(int player);
    std::vector<HexTile::REF> get_decoration_hexes(HexEntity decoration);
    std::vector<HexTile::REF> get_castles();
    std::vector<Entity::SP> get_player_units_entities(int player);
    template<std::predicate<HexTile&> Pred> std::vector<HexTile::REF> get_neighbors_if(const HexTile& from, Pred pred);
    template<std::predicate<HexTile&> Pred> std::vector<HexTile::REF> get_hexes_if(Pred pred);
    template<std::predicate<HexTile&> Pred> int count_if(Pred pred) const;

    [[nodiscard]] auto contains(const Vector3i& pos) const -> decltype(m_hex_map.contains(pos)) { return m_hex_map.contains(pos); }
    auto at(const Vector3i& pos) -> decltype(m_hex_map.at(pos)) { return m_hex_map.at(pos); }
    auto begin() -> decltype(m_hex_map.begin()) { return m_hex_map.begin(); }
    auto end() -> decltype(m_hex_map.end()) { return m_hex_map.end(); }
    [[nodiscard]] auto begin() const -> decltype(m_hex_map.begin()) { return m_hex_map.begin(); }
    [[nodiscard]] auto end() const -> decltype(m_hex_map.end()) { return m_hex_map.end(); }
    void clear();

    static constexpr std::array neighbor_directions = {
        Vector3i {1, 0, -1}, Vector3i {1, -1, 0}, Vector3i {0, -1, 1},
        Vector3i {-1, 0, 1}, Vector3i {-1, 1, 0}, Vector3i {0, 1, -1}
    };
};

#include "Konkr/Hex/HexContainer.inl"

#endif // KONKR_HEX_CONTAINER_HPP