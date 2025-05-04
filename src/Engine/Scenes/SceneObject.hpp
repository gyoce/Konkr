#ifndef ENGINE_SCENE_OBJECT_HPP
#define ENGINE_SCENE_OBJECT_HPP

#include <memory>

#include "Engine/Events/IEventHandler.hpp"

class SceneObject : public IEventHandler
{
public:
    SceneObject() = default;
    ~SceneObject() override = default;
    SceneObject(const SceneObject&) = delete;
    SceneObject(SceneObject&&) = delete;
    SceneObject& operator=(const SceneObject&) = delete;
    SceneObject& operator=(SceneObject&&) = delete;

    virtual void on_enter() {}
    virtual void update() {}
    virtual void draw() {}
    void on_key_pressed(const Event::KeyboardButton&) override {}
    void on_key_released(const Event::KeyboardButton&) override {}
    void on_mouse_button_down(const Event::MouseButton&) override {}
    void on_mouse_button_up(const Event::MouseButton&) override {}
    void on_mouse_move(const Event::MouseMove&) override {}
    void on_mouse_wheel(const Event::MouseWheel&) override {}
    void on_window_resize(const Event::WindowResize&) override {}
    void on_text_input(const Event::TextInput&) override {}

    using SP = std::shared_ptr<SceneObject>;
};

#endif // ENGINE_SCENE_OBJECT_HPP