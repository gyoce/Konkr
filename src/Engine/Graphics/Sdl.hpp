#ifndef ENGINE_SDL_HPP
#define ENGINE_SDL_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Engine/Inputs/Keyboard.hpp"
#include "Engine/Inputs/Mouse.hpp"

namespace sdl
{
    inline SDL_Renderer* g_renderer;
    inline SDL_Window* g_window;

    bool init();
    void quit();

    SDL_Texture* extract_texture_from_texture(SDL_Texture* texture, const SDL_Rect& rect);

    Keyboard::Key from_sdl_to_keyboard_key(SDL_Scancode key);
    Mouse::Button from_sdl_to_mouse_button(Uint8 button);
    SDL_Scancode from_keyboard_key_to_sdl(Keyboard::Key key);
    Uint8 from_mouse_button_to_sdl(Mouse::Button button);

} // namespace sdl

#endif // ENGINE_SDL_HPP