#include "Engine/Ui/Widgets/GuiImage.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"

void GuiImage::draw()
{
    if (!m_visible)
        return;

    if (m_texture)
        m_texture->draw(m_position, m_size);
}

void GuiImage::draw_debug()
{
    if (!m_visible)
        return;

    shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_debug_color);
}
