#include "Engine/Managers/EventManager.hpp"

#include <stdexcept>

#include "Engine/Managers/SceneManager.hpp"
#include "Engine/Graphics/Sdl.hpp"
#include "Engine/Events/Event.hpp"
#include "Engine/Utils/Logs.hpp"

EventManager* EventManager::s_instance = nullptr;

EventManager::EventManager()
{
    if (s_instance != nullptr)
    {
        logs::error("Only one EventManager can exist.");
        throw std::runtime_error("EventManager already exists");
    }
    s_instance = this;
}

void EventManager::register_on_window_leave_event(std::function<void()> callback)
{
    s_instance->m_on_window_leave_events.push_back(std::move(callback));
}

void EventManager::register_on_window_enter_event(std::function<void()> callback)
{
    s_instance->m_on_window_enter_events.push_back(std::move(callback));
}

void EventManager::register_on_key_press_event(std::function<void(Event::KeyboardButton)> callback)
{
    s_instance->m_on_key_press_events.push_back(std::move(callback));
}

void EventManager::poll_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_close_app_asked = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SceneManager::dispatch_event(Event {
                Event::MouseButton {
                    .button = sdl::from_sdl_to_mouse_button(event.button.button),
                    .state = Event::State::Pressed,
                    .position = Vector2i { event.button.x, event.button.y }
                }
            });
            break;
        case SDL_MOUSEBUTTONUP:
            SceneManager::dispatch_event(Event{
                Event::MouseButton {
                    .button = sdl::from_sdl_to_mouse_button(event.button.button),
                    .state = Event::State::Released,
                    .position = Vector2i { event.button.x , event.button.y }
                }
            });
            break;
        case SDL_MOUSEWHEEL:
            SceneManager::dispatch_event(Event {
                Event::MouseWheel {
                    .vertical_delta = event.wheel.y,
                    .horizontal_delta = event.wheel.x
                }
            });
            break;
        case SDL_MOUSEMOTION:
            SceneManager::dispatch_event(Event {
                Event::MouseMove {
                    .position = Vector2i { event.motion.x, event.motion.y }
                }
            });
            break;
        case SDL_KEYDOWN:
            SceneManager::dispatch_event(Event {
                Event::KeyboardButton {
                    .key = sdl::from_sdl_to_keyboard_key(event.key.keysym.scancode),
                    .state = Event::State::Pressed
                }
            });
            for (const auto& m_on_key_press_event : s_instance->m_on_key_press_events)
                m_on_key_press_event(Event::KeyboardButton {
                    .key = sdl::from_sdl_to_keyboard_key(event.key.keysym.scancode),
                    .state = Event::State::Pressed
                });
            break;
        case SDL_KEYUP:
            SceneManager::dispatch_event(Event {
                Event::KeyboardButton {
                    .key = sdl::from_sdl_to_keyboard_key(event.key.keysym.scancode),
                    .state = Event::State::Released
                }
            });
            break;
        case SDL_TEXTINPUT:
            SceneManager::dispatch_event(Event {
                Event::TextInput {
                    .text = event.text.text
                }
            });
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                SceneManager::dispatch_event(Event {
                    Event::WindowResize {
                        .size = Vector2i { event.window.data1, event.window.data2 }
                    }
                });
            break;
            case SDL_WINDOWEVENT_LEAVE:
                for (const auto& m_on_window_leave_event : s_instance->m_on_window_leave_events)
                    m_on_window_leave_event();
            break;
            case SDL_WINDOWEVENT_ENTER:
                for (const auto& m_on_window_enter_event : s_instance->m_on_window_enter_events)
                    m_on_window_enter_event();
            break;
            }
        break;
        }
    }
}

bool EventManager::close_app_asked()
{
    return s_instance->m_close_app_asked;
}

void EventManager::close_window()
{
    s_instance->m_close_app_asked = true;
}
