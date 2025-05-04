#include "Konkr/Widgets/SelectableOptions.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Konkr/Utils/Constants.hpp"

SelectableOptions::SelectableOptions()
{
    const GuiVerticalLayout::SP layout = std::make_shared<GuiVerticalLayout>();
    layout->set_stretch({ 1.0f, 1.0f });

    m_text_tile = std::make_shared<GuiText>();
    m_text_tile->set_stretch({ 0.5f, 0.3f });
    layout->add_widget(m_text_tile);

    m_options_layout = std::make_shared<GuiHorizontalLayout>();
    m_options_layout->set_stretch({ 1.0f, 0.7f });
    m_options_layout->set_padding_between_items({ 5, 0 });

    const GuiButton::SP button_left = std::make_shared<GuiButton>();
    button_left->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_arrow_left));
    button_left->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_arrow_left_hovered));
    button_left->set_stretch({ 0.1f, 0.4f });
    button_left->set_on_click_callback([this] { on_select_left(); });
    m_options_layout->add_widget(button_left);

    const GuiButton::SP button_right = std::make_shared<GuiButton>();
    button_right->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_arrow_right));
    button_right->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_arrow_right_hovered));
    button_right->set_stretch({ 0.1f, 0.4f });
    button_right->set_on_click_callback([this] { on_select_right(); });
    m_options_layout->add_widget(button_right);

    layout->add_layout(m_options_layout);

    GuiPanel::set_layout(layout);
}

void SelectableOptions::set_title(const std::string& title) const
{
    m_text_tile->set_text(title);
}

void SelectableOptions::set_options(const std::vector<std::string>& options)
{
    for (const std::string& option : options)
    {
        const GuiText::SP text = std::make_shared<GuiText>();
        text->set_text(option);
        text->set_stretch({ 0.7f, 1.0f });
        m_options_layout->add_widget(text, 1);
        if (!m_selectable_options.empty())
            text->hide();
        m_selectable_options.push_back(text);
    }
}

void SelectableOptions::set_selected(const int index)
{
    m_selectable_options[m_current_option]->hide();
    m_current_option = index;
    m_selectable_options[m_current_option]->show();
}

void SelectableOptions::on_select_left()
{
    m_selectable_options[m_current_option]->hide();
    m_current_option = (m_current_option - 1 + static_cast<int>(m_selectable_options.size())) % static_cast<int>(m_selectable_options.size());
    m_selectable_options[m_current_option]->show();
    if (m_on_option_selected)
        m_on_option_selected(m_current_option);
}

void SelectableOptions::on_select_right()
{
    m_selectable_options[m_current_option]->hide();
    m_current_option = (m_current_option + 1) % static_cast<int>(m_selectable_options.size());
    m_selectable_options[m_current_option]->show();
    if (m_on_option_selected)
        m_on_option_selected(m_current_option);
}
