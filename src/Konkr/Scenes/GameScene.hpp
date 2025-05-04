#ifndef KONKR_GAME_SCENE_HPP
#define KONKR_GAME_SCENE_HPP

#include "Engine/Scenes/Scene.hpp"
#include "Konkr/Hex/Map.hpp"
#include "Konkr/Managers/GameManager.hpp"
#include "Konkr/Managers/GameInteractionManager.hpp"
#include "Konkr/Widgets/EndGameWidget.hpp"
#include "Konkr/Widgets/PauseMenu.hpp"

class GameScene final : public Scene
{
public:
    void init() override;
    void on_enter() override;
    void on_key_pressed(const Event::KeyboardButton& event) override;

private:
    void setup_ui();
    void init_game_ui(const GuiVerticalLayout::SP& main_layout);
    void init_pause_menu(const GuiVerticalLayout::SP& main_layout);
    void init_endgame_menu(const GuiVerticalLayout::SP& main_layout);

    GuiPanel::SP m_game_menu = nullptr;
    PauseMenu::SP m_pause_menu = nullptr;
    EndGameWidget::SP m_endgame = nullptr;
    Map::SP m_map = nullptr;
    GameManager::SP m_game_manager = nullptr;
    GameInteractionManager::SP m_game_interaction_manager = nullptr;
};

#endif // KONKR_GAME_SCENE_HPP