#include "Engine/Ui/Layouts/GuiHorizontalLayout.hpp"

#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Ui/Widgets/GuiPanel.hpp"

void GuiHorizontalLayout::update_layout()
{
    update_widgets_size();
    update_widgets_position();
}

void GuiHorizontalLayout::add_widget(const GuiWidget::SP& widget)
{
    GuiLayout::add_widget(widget);
}

void GuiHorizontalLayout::add_widget(const GuiWidget::SP& widget, const size_t index)
{
    widget->set_parent_layout(this);
    if (index < m_widgets.size())
        m_widgets.insert(m_widgets.begin() + index, widget);
    else
        m_widgets.push_back(widget);
}

void GuiHorizontalLayout::add_layout(const GuiLayout::SP& layout)
{
    GuiLayout::add_layout(layout);
}

void GuiHorizontalLayout::add_layout(const SP& layout, const size_t index)
{
    const GuiPanel::SP layout_widget = std::make_shared<GuiPanel>();
    layout_widget->set_layout(layout);
    layout_widget->set_stretch(layout->get_stretch());
    layout_widget->set_pref_size(layout->get_pref_size());
    layout_widget->set_background_color(layout->get_background_color());
    layout_widget->set_interactable(layout->is_interactable());
    add_widget(layout_widget, index);
}

void GuiHorizontalLayout::update_widgets_position() const
{
    switch (m_horizontal_start)
    {
    case Horizontal::Left:
        update_widgets_position_left();
        break;
    case Horizontal::Center:
        update_widgets_position_center();
        break;
    case Horizontal::Right:
        update_widgets_position_right();
        break;
    }
}

void GuiHorizontalLayout::update_widgets_position_left() const
{
    float x_position_accumulated = m_parent_widget->get_position().x + m_offset_start_items.x;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.x = x_position_accumulated;
        new_position.y = get_y_pos_of_widget(widget);
        widget->set_position(new_position);
        x_position_accumulated += widget->get_size().x + m_padding_between_items.x;
    }
}

void GuiHorizontalLayout::update_widgets_position_center() const
{
    const float total_width = compute_total_children_width_with_padding();
    float x_position_accumulated = m_parent_widget->get_position().x + m_parent_widget->get_size().x / 2.0f - total_width / 2.0f + m_offset_start_items.x;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.x = x_position_accumulated;
        new_position.y = get_y_pos_of_widget(widget);
        widget->set_position(new_position);
        x_position_accumulated += widget->get_size().x + m_padding_between_items.x;
    }
}

void GuiHorizontalLayout::update_widgets_position_right() const
{
    float x_position_accumulated = m_parent_widget->get_position().x + m_parent_widget->get_size().x - m_offset_start_items.x;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.x = x_position_accumulated - widget->get_size().x;
        new_position.y = get_y_pos_of_widget(widget);
        widget->set_position(new_position);
        x_position_accumulated -= widget->get_size().x + m_padding_between_items.x;
    }
}

float GuiHorizontalLayout::get_y_pos_of_widget(const GuiWidget::SP& widget) const
{
    switch (m_vertical_align)
    {
    case Vertical::Top:
        return m_parent_widget->get_position().y + m_offset_start_items.y;
    case Vertical::Bottom:
        return m_parent_widget->get_position().y + m_parent_widget->get_size().y - widget->get_size().y - m_offset_start_items.y;
    default:
    case Vertical::Center:
        return m_parent_widget->get_position().y + (m_parent_widget->get_size().y / 2.0f - widget->get_size().y / 2.0f);
    }
}

float GuiHorizontalLayout::compute_total_children_width_with_padding() const
{
    float total_width = 0.0f;
    for (const GuiWidget::SP& widget : visible_widgets())
        total_width += widget->get_size().x + m_padding_between_items.x;
    return total_width - m_padding_between_items.x;
}
