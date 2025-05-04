#ifndef ENGINE_WINDOW_MANAGER_HPP
#define ENGINE_WINDOW_MANAGER_HPP

#include <memory>
#include <string>

#include "Engine/Math/Math.hpp"

class WindowManager
{
public:
    WindowManager();

    /// <summary>
    /// Change the title of the window with the given string.
    /// </summary>
    static void change_title(const std::string& title);

    /// <summary>
    /// Get the current size of the window.
    /// </summary>
    static Vector2i get_size();

    using UP = std::unique_ptr<WindowManager>;

private:
    /// <summary>
    /// Internal method to clear the window i.e. clear the screen.
    /// </summary>
    void clear();

    /// <summary>
    /// Internal method to display the window i.e. display the current frame.
    /// </summary>
    void display();

    static WindowManager* s_instance;

    friend class Game;
};

#endif // ENGINE_WINDOW_MANAGER_HPP