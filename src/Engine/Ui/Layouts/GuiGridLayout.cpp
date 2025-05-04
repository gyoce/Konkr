#include "Engine/Ui/Layouts/GuiGridLayout.hpp"

#include "Engine/Utils/Logs.hpp"

void GuiGridLayout::update_layout()
{
    m_cell_width = m_parent_widget->get_size().x / static_cast<float>(m_columns);
    m_cell_height = m_parent_widget->get_size().y / static_cast<float>(m_rows);
    update_widgets_size();
    update_widgets_position();
}

void GuiGridLayout::add_widget(const GuiWidget::SP& widget)
{
    GuiLayout::add_widget(widget);
}

void GuiGridLayout::add_widget(const GuiWidget::SP& widget, const int row, const int column)
{
    GuiLayout::add_widget(widget);
    set_widget_pos(widget, row, column);
}

void GuiGridLayout::add_layout(const GuiLayout::SP& layout)
{
    GuiLayout::add_layout(layout);
}

void GuiGridLayout::add_layout(const GuiLayout::SP& layout, const int row, const int column)
{
    GuiLayout::add_layout(layout);
    set_layout_pos(layout, row, column);
}

void GuiGridLayout::set_widget_pos(const GuiWidget::SP& widget, int row, int column)
{
    m_widget_positions[widget->get_id()] = { row, column };
}

void GuiGridLayout::set_layout_pos(const GuiLayout::SP& layout, int row, int column)
{
    const auto res = std::ranges::find_if(m_widgets, [&layout](const GuiWidget::SP& widget)
    {
        return widget->get_layout() == layout;
    });
    if (res == m_widgets.end())
    {
        logs::error("GuiLayout must be added in GuiGridLayout in order to set the position.");
        throw std::runtime_error("GuiLayout must be added in GuiGridLayout in, order to set the position.");
    }
    m_widget_positions[(*res)->get_id()] = { row, column };
}

void GuiGridLayout::set_grid(const int rows, const int columns)
{
    m_rows = rows;
    m_columns = columns;
}

void GuiGridLayout::update_widgets_size()
{
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        widget->set_size(Vector2f { m_cell_width, m_cell_height } - m_padding_items * 2.0f);
    }
}

void GuiGridLayout::update_widgets_position()
{
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        if (!m_widget_positions.contains(widget->get_id()))
        {
            logs::error("GuiWidget of id {} must be call with set_widget_pos in GuiGridLayout.", widget->get_id());
            throw std::runtime_error("GuiWidget must be call with set_widget_pos in GuiGridLayout.");
        }
        const auto& [row, column] = m_widget_positions.at(widget->get_id());
        Vector2f new_position{};
        new_position.x = m_parent_widget->get_position().x + static_cast<float>(column) * m_cell_width + m_padding_items.x;
        new_position.y = m_parent_widget->get_position().y + static_cast<float>(row) * m_cell_height + m_padding_items.y;
        widget->set_position(new_position);
    }
}
