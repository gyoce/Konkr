#include "Engine/Ui/Widgets/GuiButton.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Managers/GuiManager.hpp"

void GuiButton::set_on_click_callback(std::function<void()> callback)
{
    m_on_click_callback = std::move(callback);
}

void GuiButton::set_text(std::string text)
{
    m_text.set_text(std::move(text));
}

GuiButton::GuiButton()
{
    m_clickable = true;
}

void GuiButton::set_size(const Vector2f& size)
{
    m_size = size;
    m_text.set_size(size - m_text_padding * 2.0f);
}

void GuiButton::set_position(const Vector2f& position)
{
    m_position = position;
    m_text.set_position(position + m_text_padding);
}

void GuiButton::on_mouse_button_up(const Event::MouseButton& event)
{
    if (!m_visible || m_disable)
        return;

    if (contains(event.position.cast<float>()))
    {
        if (m_on_click_callback)
            m_on_click_callback();
        m_hovered = false;
    }
}

void GuiButton::on_key_pressed(const Event::KeyboardButton& event)
{
    if (!m_visible || m_disable)
        return;

    if (event.key == m_key_binding)
    {
        if (m_on_click_callback)
            m_on_click_callback();
        m_hovered = false;
    }
}

void GuiButton::draw()
{
    if (!m_visible)
        return;

    if (m_hovered)
    {
        if (m_background_texture_hovered)
            m_background_texture_hovered->draw(m_position, m_size);
        else if (m_background_texture)
            m_background_texture->draw(m_position, m_size);
    }
    else if (m_background_texture)
        m_background_texture->draw(m_position, m_size);
    m_text.draw();
}

void GuiButton::draw_debug()
{
    if (!m_visible)
        return;

    shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_debug_color);
    m_text.draw_debug();
}
