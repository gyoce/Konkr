#include "Engine/Ui/Layouts/GuiLayout.hpp"

#include <algorithm>

#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Ui/Widgets/GuiPanel.hpp"
#include "Engine/Ui/Widgets/GuiWidget.hpp"

void GuiLayout::update()
{
    for (const GuiWidget::SP& widget : m_widgets)
        widget->update();
}

void GuiLayout::draw()
{
    for (const GuiWidget::SP& widget : m_widgets)
        widget->draw();
}

void GuiLayout::draw_debug()
{
    for (const GuiWidget::SP& widget : m_widgets)
        widget->draw_debug();
}

void GuiLayout::clear()
{
    m_widgets.clear();
}

void GuiLayout::add_widget(const GuiWidget::SP& widget)
{
    widget->set_parent_layout(this);
    m_widgets.push_back(widget);
}

void GuiLayout::add_layout(const SP& layout)
{
    const GuiPanel::SP layout_widget = std::make_shared<GuiPanel>();
    layout_widget->set_layout(layout);
    layout_widget->set_stretch(layout->get_stretch());
    layout_widget->set_pref_size(layout->get_pref_size());
    layout_widget->set_background_color(layout->get_background_color());
    layout_widget->set_interactable(layout->is_interactable());
    add_widget(layout_widget);
}

bool GuiLayout::is_on_interactable_element(const Vector2f& point)
{
    return std::ranges::any_of(visible_widgets(), [&point](const GuiWidget::SP& widget)
    {
        return widget->is_on_interactable_element(point);
    });
}

bool GuiLayout::is_on_clickable_element(const Vector2f& point)
{
    return std::ranges::any_of(visible_widgets(), [&point](const GuiWidget::SP& widget)
    {
        return widget->is_on_clickable_element(point);
    });
}

bool GuiLayout::is_on_disable_element(const Vector2f& point)
{
    return std::ranges::any_of(visible_widgets(), [&point](const GuiWidget::SP& widget)
    {
        return widget->is_on_disable_element(point);
    });
}

void GuiLayout::on_mouse_move(const Event::MouseMove& event)
{
    for (const GuiWidget::SP& widget : visible_widgets())
        widget->on_mouse_move(event);
}

void GuiLayout::on_mouse_button_down(const Event::MouseButton& event)
{
    for (const GuiWidget::SP& widget : visible_widgets())
        widget->on_mouse_button_down(event);
}

void GuiLayout::on_mouse_button_up(const Event::MouseButton& event)
{
    for (const GuiWidget::SP& widget : visible_widgets())
        widget->on_mouse_button_up(event);
}

void GuiLayout::on_key_pressed(const Event::KeyboardButton& event)
{
    for (const GuiWidget::SP& widget : visible_widgets())
        widget->on_key_pressed(event);
}

void GuiLayout::on_text_input(const Event::TextInput& event)
{
    for (const GuiWidget::SP& widget : visible_widgets())
        widget->on_text_input(event);
}

void GuiLayout::update_widgets_size()
{
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        if (widget->get_strech() != Vector2f::Zero)
            widget->set_size(m_parent_widget->get_size() * widget->get_strech());
        else if (widget->get_pref_size_factor() != Vector2f::Zero)
            widget->set_size(WindowManager::get_size().cast<float>() / widget->get_pref_size_factor());
    }
}
