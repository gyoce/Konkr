#include "Engine/Managers/GuiManager.hpp"

bool GuiManager::debug_mode = false;

void GuiManager::update()
{
    m_main_widget.update();
}

void GuiManager::draw()
{
    if (debug_mode)
        m_main_widget.draw_debug();
    else
        m_main_widget.draw();
}

bool GuiManager::is_on_interactable_ui_element(const Vector2f& point) const
{
    return m_main_widget.is_on_interactable_element(point);
}

bool GuiManager::is_on_clickable_ui_element(const Vector2f& point) const
{
    return m_main_widget.is_on_clickable_element(point);
}

bool GuiManager::is_on_disable_ui_element(const Vector2f& point)
{
    return m_main_widget.is_on_disable_element(point);
}

void GuiManager::on_mouse_move(const Event::MouseMove& event)
{
    m_main_widget.on_mouse_move(event);
}

void GuiManager::on_mouse_button_down(const Event::MouseButton& event)
{
    m_main_widget.on_mouse_button_down(event);
}

void GuiManager::on_mouse_button_up(const Event::MouseButton& event)
{
    m_main_widget.on_mouse_button_up(event);
}

void GuiManager::on_window_resize(const Event::WindowResize& event)
{
    m_main_widget.set_size(event.size.cast<float>());
}

void GuiManager::on_text_input(const Event::TextInput& event)
{
    m_main_widget.on_text_input(event);
}

void GuiManager::on_key_pressed(const Event::KeyboardButton& event)
{
    m_main_widget.on_key_pressed(event);
}

void GuiManager::set_layout(const GuiLayout::SP& layout)
{
    m_main_widget.set_layout(layout);
}
