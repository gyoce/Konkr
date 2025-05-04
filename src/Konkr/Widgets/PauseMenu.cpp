#include "Konkr/Widgets/PauseMenu.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Konkr/Utils/Constants.hpp"

PauseMenu::PauseMenu()
{
    GuiPanel::set_background_color({ 0, 0, 0, 128 });
    GuiWidget::set_stretch({ 1.0f, 1.0f });
    GuiWidget::set_interactable(true);

    const GuiVerticalLayout::SP main_panel_layout = std::make_shared<GuiVerticalLayout>();
    main_panel_layout->set_stretch({ 1.0f, 1.0f });
    GuiWidget::set_layout(main_panel_layout);

    // TOP PANEL
    const GuiHorizontalLayout::SP top_panel = std::make_shared<GuiHorizontalLayout>();
    top_panel->set_stretch({ 1.0f, 0.1f });
    top_panel->set_horizontal_start(Horizontal::Right);
    top_panel->set_offset_start_items({ 20, 0 });
    main_panel_layout->add_layout(top_panel);

    const GuiButton::SP close_pause_button = std::make_shared<GuiButton>();
    close_pause_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_cross));
    close_pause_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_cross_hovered));
    close_pause_button->set_pref_size({ 32, 32 });
    close_pause_button->set_on_click_callback([this] { toggle_pause_menu(); });
    top_panel->add_widget(close_pause_button);

    // MIDDLE PANEL
    const GuiVerticalLayout::SP middle_panel = std::make_shared<GuiVerticalLayout>();
    middle_panel->set_stretch({ 1.0f, 0.9f });
    middle_panel->set_padding_between_items({ 0, 20 });
    middle_panel->set_offset_start_items({ 0, -20 });

    const GuiButton::SP back_menu_button = std::make_shared<GuiButton>();
    back_menu_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    back_menu_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    back_menu_button->set_pref_size({ 144, 48 });
    back_menu_button->set_text_padding({ 20, 10 });
    back_menu_button->set_text("Back to Menu");
    back_menu_button->set_on_click_callback([] { SceneManager::change_scene(0); });
    middle_panel->add_widget(back_menu_button);

    const GuiButton::SP quit_menu_button = std::make_shared<GuiButton>();
    quit_menu_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_red_button));
    quit_menu_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_red_button_hovered));
    quit_menu_button->set_pref_size({ 144, 48 });
    quit_menu_button->set_text_padding({ 20, 10 });
    quit_menu_button->set_text("Quit Game");
    quit_menu_button->set_on_click_callback([] { Scene::quit_game(); });
    middle_panel->add_widget(quit_menu_button);

    main_panel_layout->add_layout(middle_panel);
}

void PauseMenu::toggle_pause_menu()
{
    m_pause = !m_pause;
    if (m_pause)
    {
        show();
        if (m_associated_widget)
            m_associated_widget->hide();
    }
    else
    {
        hide();
        if (m_associated_widget)
            m_associated_widget->show();
    }
}
