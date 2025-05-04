#include "Engine/Ui/Widgets/GuiWidget.hpp"

#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Ui/Layouts/GuiLayout.hpp"
#include "Engine/Utils/Random.hpp"

namespace
{
    Color get_next_debug_color()
    {
        return Color {
            static_cast<std::uint8_t>(engine_random::next(0, 255)),
            static_cast<std::uint8_t>(engine_random::next(0, 255)),
            static_cast<std::uint8_t>(engine_random::next(0, 255)),
            255
        };
    }
}

int GuiWidget::s_id_counter = 0;

GuiWidget::GuiWidget()
    : m_id(s_id_counter++)
{
    m_debug_color = get_next_debug_color();
}

void GuiWidget::set_position(const Vector2f& position)
{
    m_position = position;
    update_layout();
}

void GuiWidget::set_pref_size(const Vector2f& size)
{
    if (size == Vector2f::Zero)
        return;

    m_size = size;
    m_pref_size_factor = WindowManager::get_size().cast<float>() / size;
}

void GuiWidget::set_layout(GuiLayout::SP layout)
{
    m_layout = std::move(layout);
    m_layout->set_parent_widget(this);
}

void GuiWidget::update_layout()
{
    if (m_layout)
        m_layout->update_layout();
}

void GuiWidget::hide()
{
    m_visible = false;
    if (m_parent_layout)
        m_parent_layout->update_layout();
    else
        update_layout();
}

void GuiWidget::show()
{
    m_visible = true;
    if (m_parent_layout)
        m_parent_layout->update_layout();
    else
        update_layout();
}

void GuiWidget::set_size(const Vector2f& size)
{
    m_size = size;
    update_layout();
}

bool GuiWidget::contains(const Vector2f& point) const
{
    return point.x >= m_position.x && point.x <= m_position.x + m_size.x &&
           point.y >= m_position.y && point.y <= m_position.y + m_size.y;
}

bool GuiWidget::is_on_interactable_element(const Vector2f& point) const
{
    if (m_visible && m_interactable && contains(point))
        return true;

    if (m_layout)
        return m_layout->is_on_interactable_element(point);

    return false;
}

bool GuiWidget::is_on_clickable_element(const Vector2f& point) const
{
    if (m_visible && m_interactable && m_clickable && contains(point))
        return true;

    if (m_layout)
        return m_layout->is_on_clickable_element(point);

    return false;
}

bool GuiWidget::is_on_disable_element(const Vector2f& point) const
{
    if (m_visible && m_disable && contains(point))
        return true;

    if (m_layout)
        return m_layout->is_on_disable_element(point);

    return false;
}

void GuiWidget::update()
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->update();
}

void GuiWidget::on_mouse_move(const Event::MouseMove& event)
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->on_mouse_move(event);
    else
        m_hovered = contains(event.position.cast<float>()) && !m_disable;
}

void GuiWidget::on_mouse_button_down(const Event::MouseButton& event)
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->on_mouse_button_down(event);
}

void GuiWidget::on_mouse_button_up(const Event::MouseButton& event)
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->on_mouse_button_up(event);
}

void GuiWidget::on_key_pressed(const Event::KeyboardButton& event)
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->on_key_pressed(event);
}

void GuiWidget::on_text_input(const Event::TextInput& event)
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->on_text_input(event);
}

void GuiWidget::draw()
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->draw();
}

void GuiWidget::draw_debug()
{
    if (!m_visible)
        return;

    if (m_layout)
        m_layout->draw_debug();
}
