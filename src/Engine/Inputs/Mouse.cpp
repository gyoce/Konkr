#include "Engine/Inputs/Mouse.hpp"

#include <SDL.h>

bool Mouse::is_button_down(const Button button)
{
    const Uint32 state = SDL_GetMouseState(nullptr, nullptr);
    switch (button)
    {
    case Left:
        return state & SDL_BUTTON(SDL_BUTTON_LEFT);
    case Right:
        return state & SDL_BUTTON(SDL_BUTTON_RIGHT);
    case Middle:
        return state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    }
    return false;
}

Vector2i Mouse::get_position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { x, y };
}
