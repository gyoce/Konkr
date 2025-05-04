#include "Konkr/Hex/Map.hpp"

#include <algorithm>
#include <numbers>
#include <ranges>
#include <cmath>

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Inputs/Keyboard.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/TimeManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Utils/Logs.hpp"

void Map::update()
{
    const float delta_time = TimeManager::get_delta_time();
    const float speed = Keyboard::is_key_pressed(Keyboard::Key::L_Shift) ? 2.0f : 1.0f;
    if (Keyboard::is_key_pressed(Keyboard::Key::Left) || Keyboard::is_key_pressed(Keyboard::Key::A))
        m_map_offset.x -= constants::hex_map_move_velocity * delta_time * speed;
    if (Keyboard::is_key_pressed(Keyboard::Key::Right) || Keyboard::is_key_pressed(Keyboard::Key::D))
        m_map_offset.x += constants::hex_map_move_velocity * delta_time * speed;
    if (Keyboard::is_key_pressed(Keyboard::Key::Up) || Keyboard::is_key_pressed(Keyboard::Key::W))
        m_map_offset.y -= constants::hex_map_move_velocity * delta_time * speed;
    if (Keyboard::is_key_pressed(Keyboard::Key::Down) || Keyboard::is_key_pressed(Keyboard::Key::S))
        m_map_offset.y += constants::hex_map_move_velocity * delta_time * speed;
}

void Map::draw()
{
    shape_drawer::draw_rect(m_background_rect, constants::background_color);
    for (const HexTile& hex : m_map | std::views::values)
        draw_hex(hex);
}

void Map::on_mouse_wheel(const Event::MouseWheel& event)
{
    if (event.vertical_delta > 0)
    {
        m_hex_size += constants::hex_size_step;
        m_hex_size = std::min(m_hex_size, constants::max_hex_size);
    }
    else if (event.vertical_delta < 0)
    {
        m_hex_size -= constants::hex_size_step;
        m_hex_size = std::max(m_hex_size, constants::min_hex_size);
    }
}

void Map::on_enter()
{
    m_map_offset.x = m_map_offset.y = 0.0f;
    m_hex_size = constants::initial_hex_size;
}

void Map::on_key_pressed(const Event::KeyboardButton& event)
{
    if (event.key == Keyboard::Key::R)
    {
        m_map_offset.x = m_map_offset.y = 0.0f;
        m_hex_size = constants::initial_hex_size;
    }
}

void Map::on_mouse_button_down(const Event::MouseButton& event)
{
    if (event.button != Mouse::Left)
        return;

    const std::optional<HexTile::REF> hex = get_hex_by_screen_coords(event.position);
    if (!hex.has_value() || (hex.has_value() && !hex.value().get().has_foreground()))
    {
        dragging = true;
        start_drag = event.position.cast<float>();
    }
}

void Map::on_mouse_button_up(const Event::MouseButton& event)
{
    if (event.button != Mouse::Left)
        return;

    dragging = false;
}

void Map::on_mouse_move(const Event::MouseMove& event)
{
    if (!dragging)
        return;

    m_map_offset -= event.position.cast<float>() - start_drag;
    start_drag = event.position.cast<float>();
}

void Map::on_window_resize(const Event::WindowResize& event)
{
    m_map_origin = event.size.cast<float>() / 2.0f;
    m_background_rect.w = event.size.x;
    m_background_rect.h = event.size.y;
}

std::optional<HexTile::REF> Map::get_hex_by_screen_coords(const Vector2i& position)
{
    const Vector3i coords = get_hex_coords_by_screen_coords(position);

    for (HexTile& hex : m_map | std::views::values)
        if (hex.is(coords))
            return std::ref(hex);

    return std::nullopt;
}

Vector3i Map::get_hex_coords_by_screen_coords(const Vector2i& position) const
{
    const Vector2f point = (position.cast<float>() + m_map_offset - m_map_origin) / m_hex_size;

    const float q = std::numbers::sqrt3_v<float> / 3.0f * point.x - 1.0f / 3.0f * point.y;
    const float r = 2.0f / 3.0f * point.y;
    const float s = -q - r;

    float q_rounded = std::round(q);
    float r_rounded = std::round(r);
    float s_rounded = std::round(s);

    const float q_diff = std::abs(q_rounded - q);
    const float r_diff = std::abs(r_rounded - r);
    const float s_diff = std::abs(s_rounded - s);

    if (q_diff > r_diff && q_diff > s_diff)
        q_rounded = -r_rounded - s_rounded;
    else if (r_diff > s_diff)
        r_rounded = -q_rounded - s_rounded;
    else
        s_rounded = -q_rounded - r_rounded;

    return Vector3i{ static_cast<int>(q_rounded), static_cast<int>(r_rounded), static_cast<int>(s_rounded) };
}

Vector2f Map::get_decoration_size(const Texture::SP& sprite_decoration, const SpriteType decoration_sprite_type) const
{
    const float factor = constants::get_sprite_decoration_factor(decoration_sprite_type);
    Vector2f decoration_size = sprite_decoration->get_size();
    const Vector2f max_size{ std::numbers::sqrt3_v<float> * m_hex_size * factor, m_hex_size * factor };
    const float scale = std::min(max_size.x / decoration_size.x, max_size.y / decoration_size.y);
    decoration_size *= scale;
    return decoration_size;
}

void Map::draw_hex(const HexTile& hex) const
{
    const Vector2f center_pixel = get_hex_center_pixel(hex);
    const Vector2f pixel_top_left {
        center_pixel.x - std::numbers::sqrt3_v<float> * m_hex_size / 2.0f,
        center_pixel.y - m_hex_size
    };
    const Vector2f hex_size {
        std::ceil(std::numbers::sqrt3_v<float> * m_hex_size),
        std::ceil(2.0f * m_hex_size)
    };
    const Texture::SP& sprite_tile = hex.get_sprite_tile();
    sprite_tile->draw(pixel_top_left, hex_size);
    if (hex.has_foreground())
    {
        const Texture::SP& sprite_decoration = hex.get_sprite_decoration();
        const Vector2f decoration_size = get_decoration_size(hex.get_sprite_decoration(), hex.get_sprite_type_decoration());
        Vector2f decoration_top_left = center_pixel - decoration_size / 2.0f;
        if (hex.get_entity()->bouncing)
            decoration_top_left.y -= hex.get_entity()->bounce_offset;
        sprite_decoration->draw(decoration_top_left, decoration_size);
    }
    if (hex.highlighted)
    {
        const Texture::SP& sprite_highlighted = ResourceManager::get_sprite(sprite_names::hightlighted);
        sprite_highlighted->draw(pixel_top_left, hex_size);
    }
    for (const Texture::SP& sprite : hex.get_fence_sprites())
        sprite->draw(pixel_top_left, hex_size);
}

void Map::clear()
{
    m_map.clear();
    m_map_offset = { 0.0f, 0.0f };
    m_hex_size = constants::initial_hex_size;
}

Vector2f Map::get_hex_center_pixel(const HexTile& hex) const
{
    static constexpr float f0 = std::numbers::sqrt3_v<float>;
    static constexpr float f1 = std::numbers::sqrt3_v<float> / 2.0f;
    static constexpr float f2 = 0.0f;
    static constexpr float f3 = 3.0f / 2.0f;
    return {
        ((f0 * static_cast<float>(hex.q()) + f1 * static_cast<float>(hex.r())) * m_hex_size + m_map_origin.x - m_map_offset.x),
        ((f2 * static_cast<float>(hex.q()) + f3 * static_cast<float>(hex.r())) * m_hex_size + m_map_origin.y - m_map_offset.y)
    };
}
