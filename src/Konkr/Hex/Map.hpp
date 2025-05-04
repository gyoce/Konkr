#ifndef KONKR_MAP_HPP
#define KONKR_MAP_HPP

#include <optional>

#include "Engine/Scenes/SceneObject.hpp"
#include "Konkr/Hex/HexContainer.hpp"
#include "Konkr/Utils/Constants.hpp"

class Map final : public SceneObject
{
public:
    Map() = default;

    void update() override;
    void draw() override;
    void draw_hex(const HexTile& hex) const;

    void on_enter() override;
    void on_key_pressed(const Event::KeyboardButton& event) override;
    void on_mouse_wheel(const Event::MouseWheel& event) override;
    void on_mouse_button_down(const Event::MouseButton& event) override;
    void on_mouse_button_up(const Event::MouseButton& event) override;
    void on_mouse_move(const Event::MouseMove& event) override;
    void on_window_resize(const Event::WindowResize& event) override;

    void set_map(HexContainer map) { m_map = std::move(map); }
    [[nodiscard]] std::optional<HexTile::REF> get_hex_by_screen_coords(const Vector2i& position);
    [[nodiscard]] Vector3i get_hex_coords_by_screen_coords(const Vector2i& position) const;
    [[nodiscard]] Vector2f get_decoration_size(const Texture::SP& sprite_decoration, SpriteType decoration_sprite_type) const;
    [[nodiscard]] HexContainer& get_map() { return m_map; }
    [[nodiscard]] bool is_dragging() const { return dragging; }
    void clear();

    using SP = std::shared_ptr<Map>;

private:
    [[nodiscard]] Vector2f get_hex_center_pixel(const HexTile& hex) const;

    HexContainer m_map;
    Vector2f m_map_offset{};
    Vector2f m_map_origin{};
    float m_hex_size{ constants::initial_hex_size };
    Recti m_background_rect{};
    bool dragging = false;
    Vector2f start_drag{};
};

#endif // KONKR_MAP_HPP