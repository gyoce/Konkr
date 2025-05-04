#ifndef ENGINE_EVENT_MANAGER_HPP
#define ENGINE_EVENT_MANAGER_HPP

#include <functional>
#include <memory>

#include "Engine/Events/Event.hpp"

class EventManager
{
public:
    EventManager();

    /// <summary>
    /// Can check if the application is asked to close i.e. the user clicked the close button of the window.
    /// </summary>
    static bool close_app_asked();

    /// <summary>
    /// Can for the application to close.
    /// </summary>
    static void close_window();

    /// <summary>
    /// Register a callback to be called when the mouse enters the window.
    /// </summary>
    static void register_on_window_enter_event(std::function<void()> callback);

    /// <summary>
    /// Register a callback to be called when the mouse leaves the window.
    /// </summary>
    static void register_on_window_leave_event(std::function<void()> callback);

    /// <summary>
    /// Register a callback to be called when a key is pressed.
    /// </summary>
    static void register_on_key_press_event(std::function<void(Event::KeyboardButton)> callback);

    using UP = std::unique_ptr<EventManager>;

private:
    /// <summary>
    /// Internal method to poll events from the application i.e. mouse, keyboard, window events.
    /// </summary>
    void poll_events();

    bool m_close_app_asked = false;
    std::vector<std::function<void()>> m_on_window_enter_events;
    std::vector<std::function<void()>> m_on_window_leave_events;
    std::vector<std::function<void(Event::KeyboardButton)>> m_on_key_press_events;

    static EventManager* s_instance;
    friend class Game;
};

#endif // ENGINE_EVENT_MANAGER_HPP