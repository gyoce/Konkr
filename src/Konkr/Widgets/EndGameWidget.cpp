#include "EndGameWidget.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Engine/Ui/Widgets/GuiPanel.hpp"
#include "Konkr/Utils/Constants.hpp"

EndGameWidget::EndGameWidget()
{
    GuiPanel::set_background_color({ 0, 0, 0, 128 });
    GuiWidget::set_stretch({ 1.0f, 1.0f });
    GuiWidget::set_interactable(true);

    const GuiVerticalLayout::SP main_panel_layout = std::make_shared<GuiVerticalLayout>();
    main_panel_layout->set_stretch({ 1.0f, 1.0f });
    GuiWidget::set_layout(main_panel_layout);

    const GuiAnchorLayout::SP ranking_layout = std::make_shared<GuiAnchorLayout>();
    ranking_layout->set_stretch({ 1.0f, 0.8f });

    const GuiPanel::SP ranking_panel = std::make_shared<GuiPanel>();
    ranking_panel->set_stretch({ 0.8f, 1.0f });
    ranking_layout->add_widget(ranking_panel, Horizontal::Center, Vertical::Center);

    const GuiHorizontalLayout::SP ranking_horizontal_layout = std::make_shared<GuiHorizontalLayout>();
    ranking_horizontal_layout->set_stretch({ 1.0f, 1.0f });
    ranking_horizontal_layout->set_padding_between_items({ 10.0f, 0.0f });
    ranking_panel->set_layout(ranking_horizontal_layout);

    // 2nd sub-panel : Column for first
    const GuiVerticalLayout::SP first_column = std::make_shared<GuiVerticalLayout>();
    first_column->set_stretch({ 0.4f, 1.0f });

    const GuiPanel::SP first_spacer = std::make_shared<GuiPanel>();
    first_spacer->set_stretch({ 1.0f, 0.2f });
    first_column->add_widget(first_spacer);

    const GuiText::SP first_label = std::make_shared<GuiText>();
    first_label->set_text("1st");
    first_label->set_stretch({ 1.0f, 0.1f });
    first_column->add_widget(first_label);

    GuiText::SP& first_name_label = m_players_name.emplace_back(new GuiText());
    first_name_label->set_text("Player 1");
    first_name_label->set_stretch({ 1.0f, 0.1f });
    first_column->add_widget(first_name_label);

    const GuiPanel::SP first_podium = std::make_shared<GuiPanel>();
    first_podium->set_background_color({ 255, 215, 0, 255 });
    first_podium->set_stretch({ 1.0f, 0.6f });
    first_column->add_widget(first_podium);

    // 1st sub-panel : Column for second
    const GuiVerticalLayout::SP second_column = std::make_shared<GuiVerticalLayout>();
    second_column->set_stretch({ 0.25f, 1.0f });

    const GuiPanel::SP second_spacer = std::make_shared<GuiPanel>();
    second_spacer->set_stretch({ 1.0f, 0.3f });
    second_column->add_widget(second_spacer);

    const GuiText::SP second_label = std::make_shared<GuiText>();
    second_label->set_text("2nd");
    second_label->set_stretch({ 1.0f, 0.1f });
    second_column->add_widget(second_label);

    GuiText::SP& second_name_label = m_players_name.emplace_back(new GuiText());
    second_name_label->set_text("Player 2");
    second_name_label->set_stretch({ 1.0f, 0.1f });
    second_column->add_widget(second_name_label);

    const GuiPanel::SP second_podium = std::make_shared<GuiPanel>();
    second_podium->set_background_color({ 192, 192, 192, 255 });
    second_podium->set_stretch({ 1.0f, 0.5f });
    second_column->add_widget(second_podium);

    // 3rd sub-panel : Column for third
    const GuiVerticalLayout::SP third_column = std::make_shared<GuiVerticalLayout>();
    third_column->set_stretch({ 0.2f, 1.0f });

    const GuiPanel::SP third_spacer = std::make_shared<GuiPanel>();
    third_spacer->set_stretch({ 1.0f, 0.4f });
    third_column->add_widget(third_spacer);

    const GuiText::SP third_label = std::make_shared<GuiText>();
    third_label->set_text("3rd");
    third_label->set_stretch({ 1.0f, 0.1f });
    third_column->add_widget(third_label);

    GuiText::SP& third_player_name = m_players_name.emplace_back(new GuiText());
    third_player_name->set_text("Player 3");
    third_player_name->set_stretch({ 1.0f, 0.1f });
    third_column->add_widget(third_player_name);

    const GuiPanel::SP third_podium = std::make_shared<GuiPanel>();
    third_podium->set_background_color({ 205, 127, 50, 255 }); // Bronze color
    third_podium->set_stretch({ 1.0f, 0.4f });
    third_column->add_widget(third_podium);

    // 4th panel : Column for fourth
    const GuiVerticalLayout::SP fourth_column = std::make_shared<GuiVerticalLayout>();
    fourth_column->set_stretch({ 0.15f, 1.0f });

    const GuiPanel::SP fourth_spacer = std::make_shared<GuiPanel>();
    fourth_spacer->set_stretch({ 1.0f, 0.5f });
    fourth_column->add_widget(fourth_spacer);

    const GuiText::SP fourth_label = std::make_shared<GuiText>();
    fourth_label->set_text("4th");
    fourth_label->set_stretch({ 1.0f, 0.1f });
    fourth_column->add_widget(fourth_label);

    GuiText::SP& fourth_player_name = m_players_name.emplace_back(new GuiText());
    fourth_player_name->set_text("Player 4");
    fourth_player_name->set_stretch({ 1.0f, 0.1f });
    fourth_column->add_widget(fourth_player_name);

    const GuiPanel::SP fourth_podium = std::make_shared<GuiPanel>();
    fourth_podium->set_background_color({ 128, 128, 128, 255 }); // Gray color
    fourth_podium->set_stretch({ 1.0f, 0.3f });
    fourth_column->add_widget(fourth_podium);

    ranking_horizontal_layout->add_layout(second_column);
    ranking_horizontal_layout->add_layout(first_column);
    ranking_horizontal_layout->add_layout(third_column);
    ranking_horizontal_layout->add_layout(fourth_column);

    const GuiAnchorLayout::SP back_menu_layout = std::make_shared<GuiAnchorLayout>();
    back_menu_layout->set_stretch({ 1.0f, 0.2f });

    const GuiButton::SP back_menu_button = std::make_shared<GuiButton>();
    back_menu_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    back_menu_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    back_menu_button->set_pref_size({ 144, 48 });
    back_menu_button->set_text_padding({ 20, 10 });
    back_menu_button->set_text("Back to Menu");
    back_menu_button->set_on_click_callback([] { SceneManager::change_scene(0); });
    back_menu_layout->add_widget(back_menu_button, Horizontal::Center, Vertical::Center);

    main_panel_layout->add_layout(ranking_layout);
    main_panel_layout->add_layout(back_menu_layout);
}

void EndGameWidget::set_ranking(const std::vector<Player::REF>& ranking)
{
    int i = 0;
    for (const Player::REF& player_ref : std::views::reverse(ranking))
    {
        m_players_name[i]->set_text(player_ref.get().name);
        i++;
    }

    for (int j = i; j < static_cast<int>(m_players_name.size()); j++)
        m_players_name[j]->set_text("");

    m_associated_widget->hide();
    GuiPanel::show();
}
