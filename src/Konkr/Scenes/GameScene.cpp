#include "Konkr/Scenes/GameScene.hpp"

#include "Engine/Managers/EventManager.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Konkr/IO/MapFile.hpp"
#include "Konkr/Utils/Constants.hpp"
#include "Konkr/Widgets/EndGameWidget.hpp"
#include "Konkr/Widgets/PauseMenu.hpp"

void GameScene::init()
{
    m_map = create_scene_object<Map>();
    m_game_manager = create_scene_object<GameManager>(m_map);
    m_game_interaction_manager = create_scene_object<GameInteractionManager>(m_map, m_game_manager);

    setup_ui();
}

void GameScene::on_enter()
{
    m_map->set_map(map_file::read_map(SceneManager::get_scene_data<std::string>(constants::menu_map_selected)));
    m_pause_menu->hide();
    m_endgame->hide();
    m_game_menu->show();
    Scene::on_enter();
}

void GameScene::on_key_pressed(const Event::KeyboardButton& event)
{
    Scene::on_key_pressed(event);
    if (event.key == Keyboard::Key::Escape)
        m_pause_menu->toggle_pause_menu();
}

void GameScene::setup_ui()
{
    const GuiVerticalLayout::SP main_layout = create_layout<GuiVerticalLayout>();
    init_pause_menu(main_layout);
    init_endgame_menu(main_layout);
    init_game_ui(main_layout);
    set_layout(main_layout);
}

void GameScene::init_game_ui(const GuiVerticalLayout::SP& main_layout)
{
    m_game_menu = create_widget<GuiPanel>();
    m_game_menu->set_stretch({ 1.0f, 1.0f });
    main_layout->add_widget(m_game_menu);

    const GuiAnchorLayout::SP game_menu_layout = create_layout<GuiAnchorLayout>();
    game_menu_layout->set_stretch({ 1.0f, 1.0f });
    m_game_menu->set_layout(game_menu_layout);

    const GuiPanel::SP top_panel = create_widget<GuiPanel>();
    top_panel->set_stretch({ 1.0f, 0.075f });
    game_menu_layout->add_widget(top_panel, Horizontal::Center, Vertical::Top);

    const GuiHorizontalLayout::SP top_main_layout = create_layout<GuiHorizontalLayout>();
    top_main_layout->set_stretch({ 1.0f, 1.0f });
    top_panel->set_layout(top_main_layout);

    const GuiHorizontalLayout::SP game_menu_top_left_layout = create_layout<GuiHorizontalLayout>();
    game_menu_top_left_layout->set_stretch({ 0.2f, 1.0f });
    top_main_layout->add_layout(game_menu_top_left_layout);

    const GuiAnchorLayout::SP game_menu_top_middle_layout = create_layout<GuiAnchorLayout>();
    game_menu_top_middle_layout->set_stretch({ 0.6f, 1.0f });
    top_main_layout->add_layout(game_menu_top_middle_layout);

    const PopupWidget::SP popup_widget = create_widget<PopupWidget>();
    popup_widget->set_stretch({ 1.0f, 1.0f });
    game_menu_top_middle_layout->add_widget(popup_widget, Horizontal::Center, Vertical::Center);

    const GuiHorizontalLayout::SP game_menu_top_right_layout = create_layout<GuiHorizontalLayout>();
    game_menu_top_right_layout->set_stretch({ 0.2f, 1.0f });
    game_menu_top_right_layout->set_horizontal_start(Horizontal::Right);
    game_menu_top_right_layout->set_offset_start_items({ 20, 0 });
    top_main_layout->add_layout(game_menu_top_right_layout);

    const GuiButton::SP settings_button = create_widget<GuiButton>();
    settings_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_gearwheel));
    settings_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_gearwheel_hovered));
    settings_button->set_pref_size({ 32, 32 });
    settings_button->set_on_click_callback([this] { m_pause_menu->toggle_pause_menu(); });
    game_menu_top_right_layout->add_widget(settings_button);

    const PlayerInfoWidget::SP player_info_widget = create_widget<PlayerInfoWidget>();
    player_info_widget->set_stretch({ 1.0f, 0.1f });
    game_menu_layout->add_widget(player_info_widget, Horizontal::Center, Vertical::Bottom);

    m_game_manager->set_popup_ui(popup_widget);
    m_game_manager->set_player_ui(player_info_widget);
    m_game_manager->set_endgame_ui(m_endgame);
    m_game_interaction_manager->set_player_ui(player_info_widget);

    m_pause_menu->set_associated_widget(m_game_menu);
    m_endgame->set_associated_widget(m_game_menu);
}

void GameScene::init_pause_menu(const GuiVerticalLayout::SP& main_layout)
{
    m_pause_menu = create_widget<PauseMenu>();
    main_layout->add_widget(m_pause_menu);
}

void GameScene::init_endgame_menu(const GuiVerticalLayout::SP& main_layout)
{
    m_endgame = create_widget<EndGameWidget>();
    main_layout->add_widget(m_endgame);
}
