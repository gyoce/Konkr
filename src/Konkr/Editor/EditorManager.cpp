#include "Konkr/Editor/EditorManager.hpp"

#include "Engine/Utils/Logs.hpp"
#include "Konkr/IO/MapFile.hpp"

EditorManager::EditorManager(Map::SP map, EditorWidget::SP editor_widget)
    : m_map(std::move(map)), m_editor_widget(std::move(editor_widget))
{
    m_editor_widget->set_on_options_changed([this](const HexOption& option)
    {
        m_hex_tile.set_type(option.type);
        m_hex_tile.set_entity(option.entity);
        m_hex_tile.set_player(option.player);
    });
}

void EditorManager::draw()
{
    if (need_drawing)
        m_map->draw_hex(m_hex_tile);
}

void EditorManager::on_mouse_move(const Event::MouseMove& event)
{
    const Vector3i coords = m_map->get_hex_coords_by_screen_coords(event.position.cast<int>());
    if (m_hex_coords == coords)
        return;

    m_hex_coords = Vector3i::One;
    need_drawing = true;
    m_hex_tile.set_position(coords);
}

void EditorManager::on_mouse_button_down(const Event::MouseButton& event)
{
    m_save_mouse_position = event.position.cast<float>();
}

void EditorManager::on_mouse_button_up(const Event::MouseButton& event)
{
    if (event.button == Mouse::Button::Right)
    {
        m_hex_coords = m_hex_tile.get_position();
        m_map->get_map().remove_hex(m_hex_coords);
        need_drawing = false;
    }
    else if (event.button == Mouse::Button::Left && (m_save_mouse_position - event.position.cast<float>()).abs() < s_mouse_move_error)
    {
        if (m_map->get_map().contains(m_hex_tile.get_position()))
            m_map->get_map().remove_hex(m_hex_tile.get_position());
        m_map->get_map().add_hex(m_hex_tile);
    }
}

void EditorManager::save_map(const std::string& map_name) const
{
    map_file::save_map(m_map->get_map(), map_name);
}
