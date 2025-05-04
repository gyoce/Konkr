#ifndef KONKR_EDITOR_MANAGER_HPP
#define KONKR_EDITOR_MANAGER_HPP

#include "Engine/Scenes/SceneObject.hpp"
#include "Konkr/Hex/Map.hpp"
#include "Konkr/Widgets/EditorWidget.hpp"

class EditorManager final : public SceneObject
{
public:
    EditorManager(Map::SP map, EditorWidget::SP editor_widget);

    void draw() override;
    void on_mouse_move(const Event::MouseMove& event) override;
    void on_mouse_button_down(const Event::MouseButton& event) override;
    void on_mouse_button_up(const Event::MouseButton& event) override;

    void save_map(const std::string& map_name) const;

    using SP = std::shared_ptr<EditorManager>;

private:
    Map::SP m_map = nullptr;
    EditorWidget::SP m_editor_widget = nullptr;
    HexTile m_hex_tile{0, 0, 0, HexType::Territory, nullptr, 0};
    Vector3i m_hex_coords = Vector3i::One;
    Vector2f m_save_mouse_position = Vector2f::Zero;
    bool need_drawing = true;

    static constexpr Vector2f s_mouse_move_error{ 15.0f, 15.0f };
};

#endif // KONKR_EDITOR_MANAGER_HPP