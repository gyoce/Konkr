#ifndef KONKR_EDITOR_SCENE_HPP
#define KONKR_EDITOR_SCENE_HPP

#include "Engine/Scenes/Scene.hpp"
#include "Konkr/Editor/EditorManager.hpp"
#include "Konkr/Hex/Map.hpp"
#include "Konkr/Widgets/EditorWidget.hpp"
#include "Konkr/Widgets/PauseMenu.hpp"

class EditorScene final : public Scene
{
public:
    void init() override;
    void on_enter() override;
    void on_key_pressed(const Event::KeyboardButton& event) override;

private:
    void setup_ui();
    void init_save_ui(const GuiVerticalLayout::SP& main_layout);
    void init_pause_menu(const GuiVerticalLayout::SP& main_layout);
    void init_editor_ui(const GuiVerticalLayout::SP& main_layout);

    GuiPanel::SP m_editor_menu = nullptr;
    GuiPanel::SP m_save_menu = nullptr;
    PauseMenu::SP m_pause_menu = nullptr;
    Map::SP m_map = nullptr;
    GuiTextInput::SP m_save_text_input = nullptr;
    EditorManager::SP m_editor_manager = nullptr;
    EditorWidget::SP m_editor_widget = nullptr;
};

#endif // KONKR_EDITOR_SCENE_HPP