#include "Engine/Inputs/Keyboard.hpp"

#include "Engine/Graphics/Sdl.hpp"

bool Keyboard::is_key_pressed(const Key key)
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    return state[sdl::from_keyboard_key_to_sdl(key)];
}
