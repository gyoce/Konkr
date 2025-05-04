#ifndef KONKR_HEX_HPP
#define KONKR_HEX_HPP

#include "Konkr/Hex/HexEnums.hpp"
#include "Engine/Math/Math.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Konkr/Utils/Constants.hpp"
#include "Konkr/Models/Entity.hpp"

#include <functional>
#include <bitset>

class HexTile
{
public:
    HexTile() = default;
    HexTile(int q, int r, int s, HexType type, Entity::SP entity, int player);

    [[nodiscard]] const Vector3i& get_position() const { return m_position; }
    [[nodiscard]] int q() const { return m_position.x; }
    [[nodiscard]] int r() const { return m_position.y; }
    [[nodiscard]] int s() const { return m_position.z; }
    [[nodiscard]] HexType get_type() const { return m_type; }
    [[nodiscard]] int get_player() const { return m_player; }
    [[nodiscard]] SpriteType get_sprite_type_tile() const { return m_sprite_tile; }
    [[nodiscard]] SpriteType get_sprite_type_decoration() const { return m_sprite_decoration; }
    [[nodiscard]] Entity::SP get_entity() const { return m_entity; }
    [[nodiscard]] bool has_entity() const { return m_entity != nullptr; }
    [[nodiscard]] bool has_movable_decoration() const;
    [[nodiscard]] const Texture::SP& get_sprite_tile() const;
    [[nodiscard]] const Texture::SP& get_sprite_decoration() const;
    [[nodiscard]] std::vector<Texture::SP> get_fence_sprites() const;
    [[nodiscard]] bool has_foreground() const;
    [[nodiscard]] bool has_building() const;
    [[nodiscard]] bool has_unit() const;
    [[nodiscard]] bool is(const Vector3i& coords) const { return m_position == coords; }
    [[nodiscard]] HexEntity get_decoration() const;
    void set_position(const Vector3i& position) { m_position = position; }
    void set_entity(Entity::SP entity);
    void set_type(HexType type);
    void set_player(int player);
    void set_fence(HexDirection direction, bool value);
    void remove_fences();
    
    bool operator==(const HexTile& other) const;

    /// <summary>
    /// If this is true, the decoration will not be drawn.
    /// </summary>
    bool disable_decoration = false;

    /// <summary>
    /// If this is true, the tile will be highlighted i.e. it will draw a white hexagone on top of the tile.
    /// </summary>
    bool highlighted = false;

    /// <summary>
    /// If this is true, it means that the tile is safe i.e. it has a building on it or is a direct neighbor of a building.
    /// </summary>
    bool safe = false;

    /// <summary>
    /// This represents the safe level of the tile i.e. if this is 1 it means that there is a city hall in the neighborhood.
    /// </summary>
    int safe_level = 0;

    static int distance(const HexTile& from, const HexTile& to);

    struct Hash
    {
        size_t operator()(const HexTile& hex) const
        {
            return std::hash<int>()(hex.q()) ^ std::hash<int>()(hex.r()) ^ std::hash<int>()(hex.s());
        }
    };

    using REF = std::reference_wrapper<HexTile>;

private:
    void update_sprites();

    Vector3i m_position;
    HexType m_type;
    int m_player;
    std::bitset<6> m_fences{0};
    SpriteType m_sprite_tile = SpriteType::Tile0;
    SpriteType m_sprite_decoration = SpriteType::None;
    Entity::SP m_entity;
};

#endif // KONKR_HEX_HPP