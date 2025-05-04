#include "Konkr/Scenes/EditorScene.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Konkr/IO/MapFile.hpp"
#include "Konkr/Utils/Constants.hpp"
#include "Konkr/Widgets/PauseMenu.hpp"

void EditorScene::init()
{
    setup_ui();
    m_map = create_scene_object<Map>();
    m_editor_manager = create_scene_object<EditorManager>(m_map, m_editor_widget);
}

void EditorScene::on_enter()
{
    Scene::on_enter();
    m_pause_menu->hide();
    m_save_menu->hide();
    m_editor_menu->show();
    if (SceneManager::get_scene_data<bool>(constants::menu_map_new))
        m_map->clear();
    else
        m_map->set_map(map_file::read_map(SceneManager::get_scene_data<std::string>(constants::menu_map_selected)));
}

void EditorScene::on_key_pressed(const Event::KeyboardButton& event)
{
    Scene::on_key_pressed(event);
    if (event.key == Keyboard::Key::Escape)
    {
        m_pause_menu->toggle_pause_menu();
        m_save_menu->hide();
    }
}

void EditorScene::setup_ui()
{
    const GuiVerticalLayout::SP main_layout = create_layout<GuiVerticalLayout>();
    init_pause_menu(main_layout);
    init_editor_ui(main_layout);
    init_save_ui(main_layout);
    set_layout(main_layout);
}

void EditorScene::init_pause_menu(const GuiVerticalLayout::SP& main_layout)
{
    m_pause_menu = create_widget<PauseMenu>();
    main_layout->add_widget(m_pause_menu);
}

void EditorScene::init_editor_ui(const GuiVerticalLayout::SP& main_layout)
{
    m_editor_menu = create_widget<GuiPanel>();
    m_editor_menu->set_stretch({ 1.0f, 1.0f });
    main_layout->add_widget(m_editor_menu);

    const GuiAnchorLayout::SP editor_menu_layout = create_layout<GuiAnchorLayout>();
    editor_menu_layout->set_stretch({ 1.0f, 1.0f });
    m_editor_menu->set_layout(editor_menu_layout);

    // TOP PANEL
    const GuiAnchorLayout::SP editor_top_layout = create_layout<GuiAnchorLayout>();
    editor_top_layout->set_stretch({ 1.0f, 0.075f });
    editor_top_layout->set_offset_start_items({ 20, 0 });
    editor_menu_layout->add_layout(editor_top_layout, Horizontal::Center, Vertical::Top);

    const GuiButton::SP burger_button = create_widget<GuiButton>();
    burger_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_burger_menu));
    burger_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_burger_menu_hovered));
    burger_button->set_pref_size({ 32, 32 });
    burger_button->set_on_click_callback([this] { m_save_menu->show(); m_editor_menu->hide(); });
    editor_top_layout->add_widget(burger_button, Horizontal::Left, Vertical::Center);

    const GuiButton::SP settings_button = create_widget<GuiButton>();
    settings_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_gearwheel));
    settings_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_gearwheel_hovered));
    settings_button->set_pref_size({ 32, 32 });
    settings_button->set_on_click_callback([this] { m_pause_menu->toggle_pause_menu(); });
    editor_top_layout->add_widget(settings_button, Horizontal::Right, Vertical::Center);

    // BOTTOM PANEL
    m_editor_widget = create_widget<EditorWidget>();
    editor_menu_layout->add_widget(m_editor_widget, Horizontal::Center, Vertical::Bottom);

    m_pause_menu->set_associated_widget(m_editor_menu);
}

void EditorScene::init_save_ui(const GuiVerticalLayout::SP& main_layout)
{
    m_save_menu = create_widget<GuiPanel>();
    m_save_menu->set_stretch({ 1.0f, 1.0f });
    m_save_menu->set_background_color({ 0, 0, 0, 128 });
    m_save_menu->set_interactable(true);

    const GuiAnchorLayout::SP save_menu_layout = create_layout<GuiAnchorLayout>();
    save_menu_layout->set_stretch({ 1.0f, 1.0f });
    save_menu_layout->set_offset_start_items({ 0, 20 });
    m_save_menu->set_layout(save_menu_layout);

    // TOP PANEL
    const GuiHorizontalLayout::SP top_panel = create_layout<GuiHorizontalLayout>();
    top_panel->set_stretch({ 1.0f, 0.1f });
    top_panel->set_horizontal_start(Horizontal::Right);
    top_panel->set_offset_start_items({ 20, 0 });
    save_menu_layout->add_layout(top_panel, Horizontal::Center, Vertical::Top);

    const GuiButton::SP close_pause_button = create_widget<GuiButton>();
    close_pause_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_cross));
    close_pause_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_cross_hovered));
    close_pause_button->set_pref_size({ 32, 32 });
    close_pause_button->set_on_click_callback([this] { m_save_menu->hide(); m_editor_menu->show(); });
    top_panel->add_widget(close_pause_button);

    // MIDDLE PANEL
    const GuiVerticalLayout::SP save_menu_middle_panel = create_layout<GuiVerticalLayout>();
    save_menu_middle_panel->set_stretch({ 1.0f, 0.9f });
    save_menu_middle_panel->set_padding_between_items({ 0, 20 });
    save_menu_layout->add_layout(save_menu_middle_panel, Horizontal::Center, Vertical::Center);

    const GuiHorizontalLayout::SP save_text_input_panel = create_layout<GuiHorizontalLayout>();
    save_text_input_panel->set_stretch({ 0.6f, 0.15f });
    save_text_input_panel->set_padding_between_items({ 20, 0 });
    save_menu_middle_panel->add_layout(save_text_input_panel);

    const GuiText::SP save_text = create_widget<GuiText>();
    save_text->set_text("Map name :");
    save_text->set_stretch({ 0.3f, 1.0f });
    save_text->set_horizontal_align(Horizontal::Left);
    save_text_input_panel->add_widget(save_text);

    m_save_text_input = create_widget<GuiTextInput>();
    m_save_text_input->set_stretch({ 0.7f, 1.0f });
    m_save_text_input->set_background_color({ 0, 0, 0, 64 });
    save_text_input_panel->add_widget(m_save_text_input);

    const GuiButton::SP save_button = create_widget<GuiButton>();
    save_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    save_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    save_button->set_pref_size({ 144, 48 });
    save_button->set_text_padding({ 20, 10 });
    save_button->set_text("Save Map");
    save_button->set_on_click_callback([this]
    {
        m_editor_manager->save_map(m_save_text_input->get_text());
        m_save_menu->hide();
        m_editor_menu->show();
    });
    save_menu_middle_panel->add_widget(save_button);

    main_layout->add_widget(m_save_menu);
}