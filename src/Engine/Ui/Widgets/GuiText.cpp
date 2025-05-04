#include "Engine/Ui/Widgets/GuiText.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Managers/GuiManager.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"

GuiText::GuiText()
{
    m_interactable = false;
}

void GuiText::set_size(const Vector2f& size)
{
    GuiWidget::set_size(size);
    if (m_text_texture)
        compute_text_size();
}

void GuiText::set_position(const Vector2f& position)
{
    GuiWidget::set_position(position);
    compute_text_position();
}

void GuiText::set_text(std::string text, const bool refresh_parent)
{
    m_text = std::move(text);
    if (m_text.empty())
        m_text_texture = nullptr;
    else
    {
        m_text_texture = ResourceManager::get_main_font()->create_text_texture(m_text, m_text_color);
        m_size = m_text_texture->get_size();
    }

    if (refresh_parent && m_parent_layout)
        m_parent_layout->update_layout();
}

void GuiText::set_text_color(const Color color)
{
    m_text_color = color;
    if (m_text_texture)
        m_text_texture = ResourceManager::get_main_font()->create_text_texture(m_text, m_text_color);
}

void GuiText::draw()
{
    if (!m_visible)
        return;

    if (m_text_texture)
        m_text_texture->draw(m_text_position, m_text_size);
}

void GuiText::draw_debug()
{
    if (!m_visible)
        return;

    shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_debug_color);
}

void GuiText::compute_text_size()
{
    const float factor = m_text_texture->get_size().x / m_text_texture->get_size().y;
    const float target_x = m_size.y * factor;
    if (target_x <= m_size.x)
    {
        m_text_size.x = target_x;
        m_text_size.y = m_size.y;
    }
    else
    {
        m_text_size.x = m_size.x;
        m_text_size.y = m_size.x / factor;
    }
}

void GuiText::compute_text_position()
{
    m_text_position.y = m_position.y;
    switch (m_horizontal_start)
    {
    case Horizontal::Left:
        m_text_position.x = m_position.x;
        break;
    case Horizontal::Center:
        m_text_position.x = m_position.x + (m_size.x - m_text_size.x) / 2.0f;
        break;
    case Horizontal::Right:
        m_text_position.x = m_position.x + m_size.x - m_text_size.x;
        break;
    }
    if (m_text_size.y < m_size.y)
        m_text_position.y += (m_size.y - m_text_size.y) / 2.0f;
}
