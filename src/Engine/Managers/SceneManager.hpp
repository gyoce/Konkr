#ifndef ENGINE_SCENE_MANAGER_HPP
#define ENGINE_SCENE_MANAGER_HPP

#include <memory>
#include <vector>
#include <any>

#include "Engine/Scenes/Scene.hpp"

class SceneManager
{
public:
    SceneManager();

    /// <summary>
    /// Change the current scene to the one at the given index.
    /// </summary>
    static void change_scene(int scene_index);

    /// <summary>
    /// When you need to pass data between scenes, you can use this method to set the data.
    /// </summary>
    template <typename T> static void set_scene_data(const std::string& key, const T& value);

    /// <summary>
    /// When you need to pass data between scenes, you can use this method to get the data.
    /// </summary>
    template <typename T> static T get_scene_data(const std::string& key);

    /// <summary>
    /// Register a scene to the SceneManager. T has to be a derived class of Scene.
    /// </summary>
    template<class T> requires(std::derived_from<T, Scene>) void register_scene();

    using UP = std::unique_ptr<SceneManager>;

private:
    /// <summary>
    /// Internal method to call update() then draw() methods of the current scene.
    /// </summary>
    void scene_frame() const;

    /// <summary>
    /// Internal method to dispatch events to the current scene.
    /// </summary>
    static void dispatch_event(const Event& event);

    std::vector<Scene::UP> s_scenes;
    Scene* m_current_scene = nullptr;
    std::unordered_map<std::string, std::any> m_scene_data;

    static SceneManager* s_instance;

    friend class EventManager;
    friend class Game;
};

#include "Engine/Managers/SceneManager.inl"

#endif // ENGINE_SCENE_MANAGER_HPP