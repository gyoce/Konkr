#include "Engine/Ui/Widgets/GuiTextInput.hpp"

#include "Engine/Graphics/ShapeDrawer.hpp"
#include "Engine/Utils/Logs.hpp"

GuiTextInput::GuiTextInput()
{
    m_clickable = true;
    m_caret_timer.set_delay(0.75f);
    m_caret_timer.set_callback([this] { m_need_caret_draw = !m_need_caret_draw; });
    m_text_widget.set_horizontal_align(Horizontal::Left);
}

void GuiTextInput::set_size(const Vector2f& size)
{
    GuiWidget::set_size(size);
    m_caret_rect.h = size.y - m_text_padding.y * 2;
    m_text_widget.set_size(size - m_text_padding * 2.0f);
}

void GuiTextInput::set_position(const Vector2f& position)
{
    GuiWidget::set_position(position);
    m_caret_rect.x = position.x + m_text_padding.x;
    m_caret_rect.y = position.y + m_text_padding.y;
    m_text_widget.set_position(position + m_text_padding);
}

void GuiTextInput::draw()
{
    if (!m_visible)
        return;

    GuiWidget::draw();

    if (m_background_color != Color::None)
        shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_background_color);

    if (m_focus && m_need_caret_draw)
        shape_drawer::draw_rect(m_caret_rect, Color::White);

    m_text_widget.draw();
}

void GuiTextInput::draw_debug()
{
    if (!m_visible)
        return;

    shape_drawer::draw_rect(Rectf{ m_position.x, m_position.y, m_size.x, m_size.y }, m_debug_color);

    GuiWidget::draw_debug();
}

void GuiTextInput::update()
{
    m_caret_timer.update();
}

void GuiTextInput::on_mouse_button_down(const Event::MouseButton& event)
{
    if (!m_visible || m_disable)
        return;

    if (contains(event.position.cast<float>()))
    {
        SDL_StartTextInput();
        m_focus = true;
        m_caret_rect.x = m_text.empty() ? m_position.x + m_text_padding.x : m_position.x + m_text_padding.x + m_text_widget.get_text_size().x;
    }
    else
    {
        SDL_StopTextInput();
        m_focus = false;
    }
}

void GuiTextInput::on_key_pressed(const Event::KeyboardButton& event)
{
    if (event.key == Keyboard::Key::Backspace)
    {
        if (!m_text.empty())
        {
            m_text.pop_back();
            update_text_and_caret();
        }
    } 
}

void GuiTextInput::on_text_input(const Event::TextInput& event)
{
    m_text += event.text;
    update_text_and_caret();
}

void GuiTextInput::update_text_and_caret()
{
    m_text_widget.set_text(m_text);
    m_text_widget.set_size(m_size - m_text_padding * 2.0f);
    m_text_widget.set_position(m_position + m_text_padding);
    m_caret_rect.x = m_text.empty() ? m_position.x + m_text_padding.x : m_position.x + m_text_padding.x + m_text_widget.get_text_size().x;
}
