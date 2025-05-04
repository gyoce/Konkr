#include "Engine/Game.hpp"

Game::Game()
{
    m_is_init = sdl::init();
    m_window_manager = std::make_unique<WindowManager>();
    m_scene_manager = std::make_unique<SceneManager>();
    m_time_manager = std::make_unique<TimeManager>();
    m_event_manager = std::make_unique<EventManager>();
    m_resource_manager = std::make_unique<ResourceManager>();
    m_cursor = std::make_unique<Cursor>();
}

Game::~Game()
{
    m_scene_manager.reset();
    m_cursor.reset();
    m_resource_manager.reset();
    sdl::quit();
}

int Game::run()
{
    if (!m_is_init)
        return -1;

    while (!EventManager::close_app_asked())
    {
        m_time_manager->start_frame();
        m_window_manager->clear();

        frame();

        m_event_manager->poll_events();
        m_scene_manager->scene_frame();
        m_cursor->frame();

        m_window_manager->display();
        m_time_manager->end_frame();
    }
    return 0;
}