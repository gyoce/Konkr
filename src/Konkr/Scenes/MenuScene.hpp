#ifndef KONKR_MENU_SCENE_HPP
#define KONKR_MENU_SCENE_HPP

#include "Engine/Scenes/Scene.hpp"

class MenuScene final : public Scene
{
public:
    void init() override;
    void draw() override;

    void on_enter() override;
    void on_window_resize(const Event::WindowResize& event) override;

private:
    void setup_ui();
    void init_main_menu();
    void create_map_grid();
    void init_play_menu();
    void init_editor_menu();

    void on_map_selected(const std::string& map) const;

    GuiPanel::SP m_main_menu = nullptr;
    GuiPanel::SP m_play_menu = nullptr;
    GuiPanel::SP m_editor_menu = nullptr;
    GuiVerticalLayout::SP m_main_layout = nullptr;
    GuiGridLayout::SP m_select_map_grid = nullptr;
    Recti m_background_rect{};
    bool m_go_to_editor = false;
    static constexpr Color s_background_color = { 70, 160, 221, 255 };
};

#endif // KONKR_MENU_SCENE_HPP