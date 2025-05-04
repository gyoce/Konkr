#include "Engine/Ui/Layouts/GuiAnchorLayout.hpp"

#include "Engine/Utils/Logs.hpp"

void GuiAnchorLayout::update_layout()
{
    update_widgets_size();
    update_widgets_position();
}

void GuiAnchorLayout::add_widget(const GuiWidget::SP& widget)
{
    GuiLayout::add_widget(widget);
}

void GuiAnchorLayout::add_layout(const GuiLayout::SP& layout)
{
    GuiLayout::add_layout(layout);
}

void GuiAnchorLayout::add_widget(const GuiWidget::SP& widget, const Horizontal horizontal_anchor, const Vertical vertical_anchor)
{
    GuiLayout::add_widget(widget);
    set_anchor(widget, horizontal_anchor, vertical_anchor);
}

void GuiAnchorLayout::add_layout(const GuiLayout::SP& layout, const Horizontal horizontal_anchor, const Vertical vertical_anchor)
{
    GuiLayout::add_layout(layout);
    set_anchor(layout, horizontal_anchor, vertical_anchor);
}

void GuiAnchorLayout::set_anchor(const GuiWidget::SP& widget, const Horizontal horizontal_anchor, const Vertical vertical_anchor)
{
    m_widget_anchors[widget->get_id()] = { horizontal_anchor, vertical_anchor };
}

void GuiAnchorLayout::set_anchor(const GuiLayout::SP& layout, const Horizontal horizontal_anchor, const Vertical vertical_anchor)
{
    const auto res = std::ranges::find_if(m_widgets, [&layout](const GuiWidget::SP& widget)
    {
        return widget->get_layout() == layout;
    });
    if (res == m_widgets.end())
    {
        logs::error("GuiLayout must be added in GuiAnchorLayout in order to set the anchor.");
        throw std::runtime_error("GuiLayout must be added in GuiAnchorLayout in order to set the anchor.");
    }
    m_widget_anchors[(*res)->get_id()] = { horizontal_anchor, vertical_anchor };
}

void GuiAnchorLayout::update_widgets_position() const
{
    for (const GuiWidget::SP& widget : visible_widgets())
    {
        if (!m_widget_anchors.contains(widget->get_id()))
        {
            logs::error("GuiWidget of id {} must be call with set_anchor in GuiAnchorLayout.", widget->get_id());
            throw std::runtime_error("GuiWidget must be call with set_anchor in GuiAnchorLayout.");
        }

        const auto& [horizontal_anchor, vertical_anchor] = m_widget_anchors.at(widget->get_id());

        Vector2f new_position{};
        switch (horizontal_anchor)
        {
        case Horizontal::Left:
            new_position.x = m_parent_widget->get_position().x + m_offset_start_items.x;
            break;
        case Horizontal::Center:
            new_position.x = m_parent_widget->get_position().x + m_parent_widget->get_size().x / 2.0f - widget->get_size().x / 2.0f + m_offset_start_items.x;
            break;
        case Horizontal::Right:
            new_position.x = m_parent_widget->get_position().x + m_parent_widget->get_size().x - widget->get_size().x - m_offset_start_items.x;
            break;
        }
        switch (vertical_anchor)
        {
        case Vertical::Top:
            new_position.y = m_parent_widget->get_position().y + m_offset_start_items.y;
            break;
        case Vertical::Center:
            new_position.y = m_parent_widget->get_position().y + m_parent_widget->get_size().y / 2.0f - widget->get_size().y / 2.0f + m_offset_start_items.y;
            break;
        case Vertical::Bottom:
            new_position.y = m_parent_widget->get_position().y + m_parent_widget->get_size().y - widget->get_size().y - m_offset_start_items.y;
            break;
        }
        widget->set_position(new_position);
    }
}
