#include "Konkr/Scenes/MenuScene.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Konkr/IO/MapFile.hpp"
#include "Konkr/Utils/Constants.hpp"

void MenuScene::init()
{
    setup_ui();
}

void MenuScene::draw()
{
    shape_drawer::draw_rect(m_background_rect, s_background_color);
    Scene::draw();
}

void MenuScene::on_enter()
{
    Scene::on_enter();
    m_select_map_grid->clear();
    create_map_grid();
}

void MenuScene::on_window_resize(const Event::WindowResize& event)
{
    Scene::on_window_resize(event);
    m_background_rect.w = event.size.x;
    m_background_rect.h = event.size.y;
}

void MenuScene::setup_ui()
{
    m_main_layout = create_layout<GuiVerticalLayout>();

    const GuiText::SP title = create_widget<GuiText>();
    title->set_text("Konkr");
    title->set_stretch({ 0.35f, 0.2f });
    m_main_layout->add_widget(title);

    init_main_menu();
    init_play_menu();
    init_editor_menu();

    set_layout(m_main_layout);
}

void MenuScene::init_main_menu()
{
    const GuiButton::SP play_button = create_widget<GuiButton>();
    play_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    play_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    play_button->set_pref_size({ 192, 64 });
    play_button->set_text("Play");
    play_button->set_text_padding({ 40, 10 });
    play_button->set_on_click_callback([this] {
        m_main_menu->hide(); 
        m_play_menu->show();
        m_go_to_editor = false;
    });

    const GuiButton::SP editor_button = create_widget<GuiButton>();
    editor_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    editor_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    editor_button->set_pref_size({ 192, 64 });
    editor_button->set_text_padding({ 40, 10 });
    editor_button->set_text("Editor");
    editor_button->set_on_click_callback([this]
    {
        m_main_menu->hide();
        m_editor_menu->show();
    });

    const GuiButton::SP exit_button = create_widget<GuiButton>();
    exit_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_button));
    exit_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_button_hovered));
    exit_button->set_pref_size({ 192, 64 });
    exit_button->set_text_padding({ 40, 10 });
    exit_button->set_text("Exit");
    exit_button->set_on_click_callback([] { quit_game(); });

    const GuiVerticalLayout::SP main_menu_layout = create_layout<GuiVerticalLayout>();
    main_menu_layout->set_stretch({ 1.0f, 1.0f });
    main_menu_layout->set_padding_between_items({ 0, 20 });
    main_menu_layout->add_widget(play_button);
    main_menu_layout->add_widget(editor_button);
    main_menu_layout->add_widget(exit_button);

    m_main_menu = create_widget<GuiPanel>();
    m_main_menu->set_stretch({ 1.0f, 0.8f });
    m_main_menu->set_layout(main_menu_layout);
    m_main_layout->add_widget(m_main_menu);
}

void MenuScene::create_map_grid()
{
    const std::vector<std::string> maps = map_file::find_map_files(constants::path_maps);
    for (int i = 0; i < static_cast<int>(maps.size()); i++)
    {
        const GuiButton::SP map_button = create_widget<GuiButton>();
        map_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
        map_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
        map_button->set_text_padding({ 20, 10 });
        map_button->set_text(maps[i]);
        map_button->set_on_click_callback([this, maps, i] { on_map_selected(maps[i]); });
        m_select_map_grid->add_widget(map_button, i / 6, i % 6);
    }
}

void MenuScene::init_play_menu()
{
    const GuiText::SP select_map_text = create_widget<GuiText>();
    select_map_text->set_text("Select a map");
    select_map_text->set_stretch({ 0.3f, 0.15f });

    const GuiButton::SP back_button = create_widget<GuiButton>();
    back_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_button));
    back_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_button_hovered));
    back_button->set_pref_size({ 192, 64 });
    back_button->set_text("Back");
    back_button->set_text_padding({ 40, 10 });
    back_button->set_on_click_callback([this] { m_main_menu->show(); m_play_menu->hide(); });

    m_select_map_grid = create_layout<GuiGridLayout>();
    m_select_map_grid->set_stretch({ 1.0f, 0.7f });
    m_select_map_grid->set_grid(4, 6);
    m_select_map_grid->set_padding_items({ 10, 10 });

    create_map_grid();

    const GuiVerticalLayout::SP play_menu_layout = create_layout<GuiVerticalLayout>();
    play_menu_layout->set_stretch({ 1.0f, 1.0f });
    play_menu_layout->add_widget(select_map_text);
    play_menu_layout->add_layout(m_select_map_grid);
    play_menu_layout->add_widget(back_button);

    m_play_menu = create_widget<GuiPanel>();
    m_play_menu->set_stretch({ 1.0f, 0.8f });
    m_play_menu->set_layout(play_menu_layout);
    m_play_menu->hide();
    m_main_layout->add_widget(m_play_menu);
}

void MenuScene::init_editor_menu()
{
    m_editor_menu = create_widget<GuiPanel>();
    m_editor_menu->set_stretch({ 1.0f, 0.8f });
    m_editor_menu->hide();

    const GuiVerticalLayout::SP editor_first_menu_layout = create_layout<GuiVerticalLayout>();
    editor_first_menu_layout->set_stretch({ 1.0f, 1.0f });
    editor_first_menu_layout->set_padding_between_items({ 0, 20 });

    const GuiButton::SP new_map_button = create_widget<GuiButton>();
    new_map_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    new_map_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    new_map_button->set_pref_size({ 192, 64 });
    new_map_button->set_text("New Map");
    new_map_button->set_text_padding({ 20, 10 });
    new_map_button->set_on_click_callback([this]
    {
        m_editor_menu->hide();
        m_main_menu->show();
        SceneManager::set_scene_data(constants::menu_map_new, true);
        SceneManager::change_scene(2);
    });
    editor_first_menu_layout->add_widget(new_map_button);

    const GuiButton::SP modify_map_button = create_widget<GuiButton>();
    modify_map_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    modify_map_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    modify_map_button->set_pref_size({ 192, 64 });
    modify_map_button->set_text("Modify Map");
    modify_map_button->set_text_padding({ 20, 10 });
    modify_map_button->set_on_click_callback([this]
    {
        SceneManager::set_scene_data(constants::menu_map_new, false);
        m_editor_menu->hide();
        m_play_menu->show();
        m_go_to_editor = true;
    });
    editor_first_menu_layout->add_widget(modify_map_button);

    const GuiButton::SP back_button = create_widget<GuiButton>();
    back_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_button));
    back_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_button_hovered));
    back_button->set_pref_size({ 192, 64 });
    back_button->set_text("Back");
    back_button->set_text_padding({ 20, 10 });
    back_button->set_on_click_callback([this]
    {
        m_editor_menu->hide();
        m_main_menu->show();
    });
    editor_first_menu_layout->add_widget(back_button);

    m_editor_menu->set_layout(editor_first_menu_layout);
    m_main_layout->add_widget(m_editor_menu);
}

void MenuScene::on_map_selected(const std::string& map) const
{
    SceneManager::set_scene_data(constants::menu_map_selected, map);
    m_main_menu->show();
    m_play_menu->hide();
    if (m_go_to_editor)
        SceneManager::change_scene(2);
    else
        SceneManager::change_scene(1);
}
