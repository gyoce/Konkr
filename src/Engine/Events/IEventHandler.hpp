#ifndef ENGINE_I_EVENT_HANDLER_HPP
#define ENGINE_I_EVENT_HANDLER_HPP

#include "Engine/Events/Event.hpp"

class IEventHandler
{
public:
    IEventHandler() = default;
    virtual ~IEventHandler() = default;
    IEventHandler(const IEventHandler&) = delete;
    IEventHandler(IEventHandler&&) = delete;
    IEventHandler& operator=(const IEventHandler&) = delete;
    IEventHandler& operator=(IEventHandler&&) = delete;

    virtual void on_mouse_button_down(const Event::MouseButton& event) = 0;
    virtual void on_mouse_button_up(const Event::MouseButton& event) = 0;
    virtual void on_mouse_move(const Event::MouseMove& event) = 0;
    virtual void on_key_pressed(const Event::KeyboardButton& event) = 0;
    virtual void on_key_released(const Event::KeyboardButton& event) = 0;
    virtual void on_mouse_wheel(const Event::MouseWheel& event) = 0;
    virtual void on_window_resize(const Event::WindowResize& event) = 0;
    virtual void on_text_input(const Event::TextInput& event) = 0;
};

#endif // ENGINE_I_EVENT_HANDLER_HPP