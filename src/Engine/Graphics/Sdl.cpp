#include "Engine/Graphics/Sdl.hpp"

#include "Engine/Utils/Logs.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>

namespace
{
    bool g_is_init = false;
}

bool sdl::init()
{
    if (g_is_init)
        return true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logs::error("SDL_Init failed: {}", SDL_GetError());
        return false;
    }

    g_window = SDL_CreateWindow("Konkr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
    if (g_window == nullptr)
    {
        logs::error("SDL_CreateWindow failed: {}", SDL_GetError());
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (g_renderer == nullptr)
    {
        logs::error("SDL_CreateRenderer failed: {}", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

    if (TTF_Init() < 0)
    {
        logs::error("TTF_Init failed: {}", TTF_GetError());
        return false;
    }

    constexpr int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(flags) != flags)
    {
        logs::error("IMG_Init failed: {}", IMG_GetError());
        return false;
    }

    g_is_init = true;
    return true;
}

void sdl::quit()
{
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    g_is_init = false;
}

SDL_Texture* sdl::extract_texture_from_texture(SDL_Texture* texture, const SDL_Rect& rect)
{
    SDL_Texture* new_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    if (new_texture == nullptr)
    {
        logs::error("SDL_CreateTexture failed: {}", SDL_GetError());
        return nullptr;
    }
    SDL_SetRenderTarget(g_renderer, new_texture);
    SDL_RenderCopy(g_renderer, texture, &rect, nullptr);
    SDL_SetRenderTarget(g_renderer, nullptr);
    SDL_SetTextureBlendMode(new_texture, SDL_BLENDMODE_BLEND);
    return new_texture;
}

Keyboard::Key sdl::from_sdl_to_keyboard_key(const SDL_Scancode key)
{
    switch (key)
    {
    case SDL_SCANCODE_A:
        return Keyboard::Key::A;
    case SDL_SCANCODE_B:
        return Keyboard::Key::B;
    case SDL_SCANCODE_C:
        return Keyboard::Key::C;
    case SDL_SCANCODE_D:
        return Keyboard::Key::D;
    case SDL_SCANCODE_E:
        return Keyboard::Key::E;
    case SDL_SCANCODE_F:
        return Keyboard::Key::F;
    case SDL_SCANCODE_G:
        return Keyboard::Key::G;
    case SDL_SCANCODE_H:
        return Keyboard::Key::H;
    case SDL_SCANCODE_I:
        return Keyboard::Key::I;
    case SDL_SCANCODE_J:
        return Keyboard::Key::J;
    case SDL_SCANCODE_K:
        return Keyboard::Key::K;
    case SDL_SCANCODE_L:
        return Keyboard::Key::L;
    case SDL_SCANCODE_M:
        return Keyboard::Key::M;
    case SDL_SCANCODE_N:
        return Keyboard::Key::N;
    case SDL_SCANCODE_O:
        return Keyboard::Key::O;
    case SDL_SCANCODE_P:
        return Keyboard::Key::P;
    case SDL_SCANCODE_Q:
        return Keyboard::Key::Q;
    case SDL_SCANCODE_R:
        return Keyboard::Key::R;
    case SDL_SCANCODE_S:
        return Keyboard::Key::S;
    case SDL_SCANCODE_T:
        return Keyboard::Key::T;
    case SDL_SCANCODE_U:
        return Keyboard::Key::U;
    case SDL_SCANCODE_V:
        return Keyboard::Key::V;
    case SDL_SCANCODE_W:
        return Keyboard::Key::W;
    case SDL_SCANCODE_X:
        return Keyboard::Key::X;
    case SDL_SCANCODE_Y:
        return Keyboard::Key::Y;
    case SDL_SCANCODE_Z:
        return Keyboard::Key::Z;
    case SDL_SCANCODE_0:
        return Keyboard::Key::Num0;
    case SDL_SCANCODE_1:
        return Keyboard::Key::Num1;
    case SDL_SCANCODE_2:
        return Keyboard::Key::Num2;
    case SDL_SCANCODE_3:
        return Keyboard::Key::Num3;
    case SDL_SCANCODE_4:
        return Keyboard::Key::Num4;
    case SDL_SCANCODE_5:
        return Keyboard::Key::Num5;
    case SDL_SCANCODE_6:
        return Keyboard::Key::Num6;
    case SDL_SCANCODE_7:
        return Keyboard::Key::Num7;
    case SDL_SCANCODE_8:
        return Keyboard::Key::Num8;
    case SDL_SCANCODE_9:
        return Keyboard::Key::Num9;
    case SDL_SCANCODE_LEFT:
        return Keyboard::Key::Left;
    case SDL_SCANCODE_RIGHT:
        return Keyboard::Key::Right;
    case SDL_SCANCODE_UP:
        return Keyboard::Key::Up;
    case SDL_SCANCODE_DOWN:
        return Keyboard::Key::Down;
    case SDL_SCANCODE_LALT:
        return Keyboard::Key::L_Alt;
    case SDL_SCANCODE_RALT:
        return Keyboard::Key::R_Alt;
    case SDL_SCANCODE_LCTRL:
        return Keyboard::Key::L_Ctrl;
    case SDL_SCANCODE_RCTRL:
        return Keyboard::Key::R_Ctrl;
    case SDL_SCANCODE_ESCAPE:
        return Keyboard::Key::Escape;
    case SDL_SCANCODE_BACKSPACE:
        return Keyboard::Key::Backspace;
    case SDL_SCANCODE_LSHIFT:
        return Keyboard::Key::L_Shift;
    case SDL_SCANCODE_RSHIFT:
        return Keyboard::Key::R_Shift;
    default:
        return Keyboard::Key::NotRecognized;
    }
}

Mouse::Button sdl::from_sdl_to_mouse_button(const uint8_t button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return Mouse::Button::Left;
    case SDL_BUTTON_RIGHT:
        return Mouse::Button::Right;
    case SDL_BUTTON_MIDDLE:
        return Mouse::Button::Middle;
    default:
        return Mouse::Button::NotRecognized;
    }
}

SDL_Scancode sdl::from_keyboard_key_to_sdl(const Keyboard::Key key)
{
    switch (key)
    {
    case Keyboard::Key::A:
        return SDL_SCANCODE_A;
    case Keyboard::Key::B:
        return SDL_SCANCODE_B;
    case Keyboard::Key::C:
        return SDL_SCANCODE_C;
    case Keyboard::Key::D:
        return SDL_SCANCODE_D;
    case Keyboard::Key::E:
        return SDL_SCANCODE_E;
    case Keyboard::Key::F:
        return SDL_SCANCODE_F;
    case Keyboard::Key::G:
        return SDL_SCANCODE_G;
    case Keyboard::Key::H:
        return SDL_SCANCODE_H;
    case Keyboard::Key::I:
        return SDL_SCANCODE_I;
    case Keyboard::Key::J:
        return SDL_SCANCODE_J;
    case Keyboard::Key::K:
        return SDL_SCANCODE_K;
    case Keyboard::Key::L:
        return SDL_SCANCODE_L;
    case Keyboard::Key::M:
        return SDL_SCANCODE_M;
    case Keyboard::Key::N:
        return SDL_SCANCODE_N;
    case Keyboard::Key::O:
        return SDL_SCANCODE_O;
    case Keyboard::Key::P:
        return SDL_SCANCODE_P;
    case Keyboard::Key::Q:
        return SDL_SCANCODE_Q;
    case Keyboard::Key::R:
        return SDL_SCANCODE_R;
    case Keyboard::Key::S:
        return SDL_SCANCODE_S;
    case Keyboard::Key::T:
        return SDL_SCANCODE_T;
    case Keyboard::Key::U:
        return SDL_SCANCODE_U;
    case Keyboard::Key::V:
        return SDL_SCANCODE_V;
    case Keyboard::Key::W:
        return SDL_SCANCODE_W;
    case Keyboard::Key::X:
        return SDL_SCANCODE_X;
    case Keyboard::Key::Y:
        return SDL_SCANCODE_Y;
    case Keyboard::Key::Z:
        return SDL_SCANCODE_Z;
    case Keyboard::Key::Num0:
        return SDL_SCANCODE_0;
    case Keyboard::Key::Num1:
        return SDL_SCANCODE_1;
    case Keyboard::Key::Num2:
        return SDL_SCANCODE_2;
    case Keyboard::Key::Num3:
        return SDL_SCANCODE_3;
    case Keyboard::Key::Num4:
        return SDL_SCANCODE_4;
    case Keyboard::Key::Num5:
        return SDL_SCANCODE_5;
    case Keyboard::Key::Num6:
        return SDL_SCANCODE_6;
    case Keyboard::Key::Num7:
        return SDL_SCANCODE_7;
    case Keyboard::Key::Num8:
        return SDL_SCANCODE_8;
    case Keyboard::Key::Num9:
        return SDL_SCANCODE_9;
    case Keyboard::Key::Left:
        return SDL_SCANCODE_LEFT;
    case Keyboard::Key::Right:
        return SDL_SCANCODE_RIGHT;
    case Keyboard::Key::Up:
        return SDL_SCANCODE_UP;
    case Keyboard::Key::Down:
        return SDL_SCANCODE_DOWN;
    case Keyboard::Key::L_Alt:
        return SDL_SCANCODE_LALT;
    case Keyboard::Key::R_Alt:
        return SDL_SCANCODE_RALT;
    case Keyboard::Key::L_Ctrl:
        return SDL_SCANCODE_LCTRL;
    case Keyboard::Key::R_Ctrl:
        return SDL_SCANCODE_RCTRL;
    case Keyboard::Key::Escape:
        return SDL_SCANCODE_ESCAPE;
    case Keyboard::Key::Backspace:
        return SDL_SCANCODE_BACKSPACE;
    case Keyboard::Key::L_Shift:
        return SDL_SCANCODE_LSHIFT;
    case Keyboard::Key::R_Shift:
        return SDL_SCANCODE_RSHIFT;
    default:
        return SDL_SCANCODE_UNKNOWN;
    }
}

Uint8 sdl::from_mouse_button_to_sdl(const Mouse::Button button)
{
    switch (button)
    {
    case Mouse::Button::Left:
        return SDL_BUTTON_LEFT;
    case Mouse::Button::Right:
        return SDL_BUTTON_RIGHT;
    case Mouse::Button::Middle:
        return SDL_BUTTON_MIDDLE;
    default:
        return 0;
    }
}
