#include "Engine/Managers/WindowManager.hpp"

#include "Engine/Graphics/Sdl.hpp"

WindowManager* WindowManager::s_instance = nullptr;

void WindowManager::change_title(const std::string& title)
{
    SDL_SetWindowTitle(sdl::g_window, title.c_str());
}

Vector2i WindowManager::get_size()
{
    Vector2i size;
    SDL_GetWindowSize(sdl::g_window, &size.x, &size.y);
    return size;
}

WindowManager::WindowManager()
{
    s_instance = this;
}

void WindowManager::clear()
{
    SDL_SetRenderDrawColor(sdl::g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl::g_renderer);
}

void WindowManager::display()
{
    SDL_RenderPresent(sdl::g_renderer);
}
