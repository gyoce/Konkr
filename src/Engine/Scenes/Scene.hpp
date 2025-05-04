#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include <memory>
#include <vector>

#include "Engine/Events/IEventHandler.hpp"
#include "Engine/Scenes/SceneObject.hpp"
#include "Engine/Managers/GuiManager.hpp"

class Scene : public IEventHandler
{
public:
    Scene() = default;
    ~Scene() override = default;
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) = delete;

    /// <summary>
    /// Called when the scene is created i.e. when SceneManager registers this scene.
    /// </summary>
    virtual void init() {}

    /// <summary>
    /// Called when the scene is entered i.e. when SceneManager switches to this scene.
    /// You must call this method in the derived class.
    /// </summary>
    virtual void on_enter();

    /// <summary>
    /// Called once per frame, before draw(), it should contain the logic of the scene.
    /// You must call this method in the derived class.
    /// </summary>
    virtual void update();

    /// <summary>
    /// Called once per frame, after update(), it should contain the rendering of the scene.
    /// You must call this method in the derived class.
    /// </summary>
    virtual void draw();

    /// <summary>
    /// Call this method if you want to quit the game.
    /// </summary>
    static void quit_game();

    using UP = std::unique_ptr<Scene>;

protected:
    template<typename T, typename... Args> requires(std::derived_from<T, SceneObject>) std::shared_ptr<T> create_scene_object(Args&&... args);
    template<typename T, typename... Args> requires(std::derived_from<T, GuiWidget>) std::shared_ptr<T> create_widget(Args&&... args);
    template<typename T, typename... Args> requires(std::derived_from<T, GuiLayout>) std::shared_ptr<T> create_layout(Args&&... args);
    void set_layout(const GuiLayout::SP& layout);

    /// <summary>
    /// Called when there is a mouse button down event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_mouse_button_down(const Event::MouseButton& event) override;

    /// <summary>
    /// Called when there is a mouse button up event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_mouse_button_up(const Event::MouseButton& event) override;

    /// <summary>
    /// Called when there is a mouse move event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_mouse_move(const Event::MouseMove& event) override;

    /// <summary>
    /// Called when there is a key pressed event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_key_pressed(const Event::KeyboardButton& event) override;

    /// <summary>
    /// Called when there is a key released event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_key_released(const Event::KeyboardButton& event) override;

    /// <summary>
    /// Called when there is a mouse wheel event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_mouse_wheel(const Event::MouseWheel& event) override;

    /// <summary>
    /// Called when the window is resized.
    /// You must call this method in the derived class.
    /// </summary>
    void on_window_resize(const Event::WindowResize& event) override;

    /// <summary>
    /// Called when there is a text input event.
    /// You must call this method in the derived class.
    /// </summary>
    void on_text_input(const Event::TextInput& event) override;

private:
    std::vector<SceneObject::SP> m_scene_objects;
    GuiManager m_gui_manager{};

    friend class SceneManager;
};

#include "Engine/Scenes/Scene.inl"

#endif // ENGINE_SCENE_HPP