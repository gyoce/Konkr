#include "Engine/Managers/SceneManager.hpp"

#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Utils/Logs.hpp"

SceneManager* SceneManager::s_instance = nullptr;

SceneManager::SceneManager()
{
    if (s_instance != nullptr)
    {
        logs::error("Only one SceneManager can exist.");
        throw std::runtime_error("SceneManager already exists");
    }
    s_instance = this;
}

void SceneManager::change_scene(const int scene_index)
{
    if (s_instance->s_scenes.empty() || static_cast<size_t>(scene_index) >= s_instance->s_scenes.size())
    {
        logs::error("Scene index must be in range of registered scenes");
        return;
    }
    s_instance->m_current_scene = s_instance->s_scenes[scene_index].get();
    logs::message("Changing scene to {}", scene_index);

    const Vector2i window_size = WindowManager::get_size();
    dispatch_event(Event {
        Event::WindowResize {
            .size = window_size
        }
    });
    s_instance->m_current_scene->on_enter();
}

void SceneManager::scene_frame() const
{
    m_current_scene->update();
    m_current_scene->draw();
}

void SceneManager::dispatch_event(const Event& event)
{
    if (event.is<Event::MouseButton>())
    {
        if (event.get<Event::MouseButton>().state == Event::State::Pressed)
            s_instance->m_current_scene->on_mouse_button_down(event.get<Event::MouseButton>());
        else if (event.get<Event::MouseButton>().state == Event::State::Released)
            s_instance->m_current_scene->on_mouse_button_up(event.get<Event::MouseButton>());
    }
    else if (event.is<Event::KeyboardButton>())
    {
        if (event.get<Event::KeyboardButton>().state == Event::State::Pressed)
            s_instance->m_current_scene->on_key_pressed(event.get<Event::KeyboardButton>());
        else if (event.get<Event::KeyboardButton>().state == Event::State::Released)
            s_instance->m_current_scene->on_key_released(event.get<Event::KeyboardButton>());
    }
    else if (event.is<Event::MouseWheel>())
        s_instance->m_current_scene->on_mouse_wheel(event.get<Event::MouseWheel>());
    else if (event.is<Event::MouseMove>())
        s_instance->m_current_scene->on_mouse_move(event.get<Event::MouseMove>());
    else if (event.is<Event::WindowResize>())
        s_instance->m_current_scene->on_window_resize(event.get<Event::WindowResize>());
    else if (event.is<Event::TextInput>())
        s_instance->m_current_scene->on_text_input(event.get<Event::TextInput>());
}
