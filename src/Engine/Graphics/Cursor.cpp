#include "Engine/Graphics/Cursor.hpp"

#include <stdexcept>

#include "Engine/Managers/EventManager.hpp"
#include "Engine/Utils/Logs.hpp"

Cursor* Cursor::s_instance = nullptr;

Cursor::Cursor()
{
    if (s_instance != nullptr)
    {
        logs::error("Only one Cursor can exist.");
        throw std::runtime_error("Cursor already exists");
    }
    s_instance = this;

    EventManager::register_on_window_enter_event([this]
    {
        m_need_drawing = true;
    });

    EventManager::register_on_window_leave_event([this]
    {
        m_need_drawing = false;
    });
}

void Cursor::register_cursor(const Type type, Texture::SP texture)
{
    SDL_ShowCursor(SDL_DISABLE);
    s_instance->m_cursors[type] = std::move(texture);
}

void Cursor::set_active_cursor(const Type type)
{
    s_instance->m_active_cursor = type;
}

void Cursor::frame()
{
    if (!m_need_drawing || !m_cursors.contains(m_active_cursor))
        return;

    const Vector2i mouse_position = Mouse::get_position();
    const Texture::SP& cursor_texture = m_cursors[m_active_cursor];
    cursor_texture->draw(mouse_position.cast<float>(), m_cursor_size);
}
