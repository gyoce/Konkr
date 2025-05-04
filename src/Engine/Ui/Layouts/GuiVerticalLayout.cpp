#include "Engine/Ui/Layouts/GuiVerticalLayout.hpp"

#include "Engine/Managers/WindowManager.hpp"

void GuiVerticalLayout::update_layout()
{
    update_widgets_size();
    update_widgets_position();
}

void GuiVerticalLayout::update_widgets_position() const
{
    switch (m_vertical_start)
    {
    case Vertical::Top:
        update_widgets_position_top();
        break;
    case Vertical::Bottom:
        update_widgets_position_bottom();
        break;
    case Vertical::Center:
        update_widgets_position_center();
        break;
    }
}

void GuiVerticalLayout::update_widgets_position_top() const
{
    float y_position_accumulated = m_parent_widget->get_position().y + m_offset_start_items.y;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.y = y_position_accumulated;
        new_position.x = get_x_pos_of_widget(widget);
        widget->set_position(new_position);
        y_position_accumulated += widget->get_size().y + m_padding_between_items.y;
    }
}

void GuiVerticalLayout::update_widgets_position_center() const
{
    const float total_height = compute_total_widgets_height_with_padding();
    float y_position_accumulated = m_parent_widget->get_position().y + m_parent_widget->get_size().y / 2.0f - total_height / 2.0f + m_offset_start_items.y;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.y = y_position_accumulated;
        new_position.x = get_x_pos_of_widget(widget);
        widget->set_position(new_position);
        y_position_accumulated += widget->get_size().y + m_padding_between_items.y;
    }
}

void GuiVerticalLayout::update_widgets_position_bottom() const
{
    float y_position_accumulated = m_parent_widget->get_position().y + m_parent_widget->get_size().y - m_offset_start_items.y;
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        Vector2f new_position{};
        new_position.y = y_position_accumulated - widget->get_size().y;
        new_position.x = get_x_pos_of_widget(widget);
        widget->set_position(new_position);
        y_position_accumulated -= widget->get_size().y + m_padding_between_items.y;
    }
}

float GuiVerticalLayout::get_x_pos_of_widget(const GuiWidget::SP& widget) const
{
    switch (m_horizontal_align)
    {
    case Horizontal::Left:
        return m_parent_widget->get_position().x + m_offset_start_items.x;
    case Horizontal::Right:
        return m_parent_widget->get_position().x + m_parent_widget->get_size().x - widget->get_size().x - m_offset_start_items.x;
    default:
    case Horizontal::Center:
        return m_parent_widget->get_position().x + (m_parent_widget->get_size().x / 2.0f - widget->get_size().x / 2.0f);
    }
}

float GuiVerticalLayout::compute_total_widgets_height_with_padding() const
{
    float total_height = 0.0f;
    for (const GuiWidget::SP& widget : visible_widgets())
        total_height += widget->get_size().y + m_padding_between_items.y;
    return total_height - m_padding_between_items.y;
}
