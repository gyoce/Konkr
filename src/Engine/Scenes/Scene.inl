template <typename T, typename ... Args> requires(std::derived_from<T, SceneObject>)
std::shared_ptr<T> Scene::create_scene_object(Args&&... args)
{
    std::shared_ptr<T> scene_object = std::make_shared<T>(std::forward<Args>(args)...);
    m_scene_objects.push_back(scene_object);
    return scene_object;
}

template <typename T, typename ... Args> requires(std::derived_from<T, GuiWidget>)
std::shared_ptr<T> Scene::create_widget(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename ...Args> requires(std::derived_from<T, GuiLayout>)
std::shared_ptr<T> Scene::create_layout(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
