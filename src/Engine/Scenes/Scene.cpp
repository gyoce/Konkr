#include "Engine/Scenes/Scene.hpp"

#include "Engine/Graphics/Cursor.hpp"
#include "Engine/Managers/EventManager.hpp"

void Scene::on_enter()
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_enter();
}

void Scene::update()
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->update();
    m_gui_manager.update();
}

void Scene::draw()
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->draw();
    m_gui_manager.draw();
}

void Scene::quit_game()
{
    EventManager::close_window();
}

void Scene::on_key_pressed(const Event::KeyboardButton& event)
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_key_pressed(event);
    m_gui_manager.on_key_pressed(event);
}

void Scene::on_key_released(const Event::KeyboardButton& event)
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_key_released(event);
}

void Scene::set_layout(const GuiLayout::SP& layout)
{
    m_gui_manager.set_layout(layout);
}

void Scene::on_mouse_button_down(const Event::MouseButton& event)
{
    Cursor::set_active_cursor(Cursor::Type::Dragging);
    m_gui_manager.on_mouse_button_down(event);
    if (!m_gui_manager.is_on_interactable_ui_element(event.position.cast<float>()))
        for (const SceneObject::SP& scene_object : m_scene_objects)
            scene_object->on_mouse_button_down(event);
}

void Scene::on_mouse_button_up(const Event::MouseButton& event)
{
    Cursor::set_active_cursor(Cursor::Type::Idle);
    m_gui_manager.on_mouse_button_up(event);
    if (!m_gui_manager.is_on_interactable_ui_element(event.position.cast<float>()))
        for (const SceneObject::SP& scene_object : m_scene_objects)
            scene_object->on_mouse_button_up(event);
}

void Scene::on_mouse_move(const Event::MouseMove& event)
{
    m_gui_manager.on_mouse_move(event);
    if (m_gui_manager.is_on_disable_ui_element(event.position.cast<float>()))
        Cursor::set_active_cursor(Cursor::Type::Disable);
    else if (m_gui_manager.is_on_clickable_ui_element(event.position.cast<float>()))
        Cursor::set_active_cursor(Cursor::Type::Clickable);
    else if (!m_gui_manager.is_on_interactable_ui_element(event.position.cast<float>()))
    {
        if (Cursor::get_active_cursor() != Cursor::Type::Dragging)
            Cursor::set_active_cursor(Cursor::Type::Idle);
        for (const SceneObject::SP& scene_object : m_scene_objects)
            scene_object->on_mouse_move(event);
    }
    else
        Cursor::set_active_cursor(Cursor::Type::Idle);
}

void Scene::on_mouse_wheel(const Event::MouseWheel& event)
{
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_mouse_wheel(event);
}

void Scene::on_window_resize(const Event::WindowResize& event)
{
    m_gui_manager.on_window_resize(event);
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_window_resize(event);
}

void Scene::on_text_input(const Event::TextInput& event)
{
    m_gui_manager.on_text_input(event);
    for (const SceneObject::SP& scene_object : m_scene_objects)
        scene_object->on_text_input(event);
}
