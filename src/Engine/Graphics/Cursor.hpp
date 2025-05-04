#ifndef ENGINE_CURSOR_HPP
#define ENGINE_CURSOR_HPP

#include <unordered_map>

#include "Engine/Graphics/Texture.hpp"

class Cursor
{
public:
    Cursor();

    enum class Type : std::uint8_t
    {
        Idle,
        Clickable,
        Dragging,
        Disable
    };

    static void register_cursor(Type type, Texture::SP texture);
    static void set_active_cursor(Type type);
    [[nodiscard]] static Type get_active_cursor() { return s_instance->m_active_cursor; }

    using UP = std::unique_ptr<Cursor>;

private:
    std::unordered_map<Type, Texture::SP> m_cursors;
    Type m_active_cursor = Type::Idle;
    Vector2f m_cursor_size{ 32, 32 };
    bool m_need_drawing = false;

    void frame();

    static Cursor* s_instance;

    friend class Game;
};

#endif // ENGINE_CURSOR_HPP