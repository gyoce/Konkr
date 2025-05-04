#include "Engine/Ui/Widgets/GuiPanel.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Managers/GuiManager.hpp"

GuiPanel::GuiPanel()
{
    m_interactable = false;
}

void GuiPanel::draw()
{
    if (!m_visible)
        return;

    if (m_background_texture)
        m_background_texture->draw(m_position, m_size);
    else if (m_background_color != Color::None)
        shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_background_color);

    GuiWidget::draw();
}

void GuiPanel::draw_debug()
{
    if (!m_visible)
        return;

    shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_debug_color);

    GuiWidget::draw_debug();
}
