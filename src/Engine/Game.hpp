#ifndef ENGINE_GAME_HPP
#define ENGINE_GAME_HPP

#include "Engine/Managers/EventManager.hpp"
#include "Engine/Managers/SceneManager.hpp"
#include "Engine/Managers/TimeManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Graphics/Cursor.hpp"

/// <summary>
/// Base class for the game.
/// You have access to some managers like the ResourceManager and the SceneManager which are
/// used to load resources (sprites, fonts, etc.) and register scenes.
/// </summary>
class Game
{
public:
    Game();
    virtual ~Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    [[nodiscard]] int run();

    virtual void frame(){}

protected:
    ResourceManager::UP m_resource_manager = nullptr;
    SceneManager::UP m_scene_manager = nullptr;

private:
    bool m_is_init = false;
    Cursor::UP m_cursor = nullptr;
    WindowManager::UP m_window_manager = nullptr;
    TimeManager::UP m_time_manager = nullptr;
    EventManager::UP m_event_manager = nullptr;
};

#endif // ENGINE_GAME_HPP