#include "Engine/Utils/Logs.hpp"

template<class T> requires(std::derived_from<T, Scene>)
void SceneManager::register_scene()
{
    s_scenes.push_back(std::make_unique<T>());
    s_scenes.back()->init();
}

template<typename T>
void SceneManager::set_scene_data(const std::string& key, const T& value)
{
    s_instance->m_scene_data[key] = value;
}

template<typename T>
T SceneManager::get_scene_data(const std::string& key)
{
    try
    {
        return std::any_cast<T>(s_instance->m_scene_data.at(key));
    }
    catch (const std::bad_any_cast& e)
    {
        logs::error("Failed to get scene data: {}", e.what());
        throw std::runtime_error("Failed to get scene data");
    }    
}
