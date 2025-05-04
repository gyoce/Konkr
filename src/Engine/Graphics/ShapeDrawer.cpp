#include "Engine/Graphics/ShapeDrawer.hpp"

#include "Engine/Graphics/Sdl.hpp"

void shape_drawer::draw_rect(const Recti& rect, const Color& color)
{
    const SDL_Rect sdl_rect = { rect.x, rect.y, rect.w, rect.h };
    SDL_SetRenderDrawColor(sdl::g_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(sdl::g_renderer, &sdl_rect);
}

void shape_drawer::draw_rect(const Rectf& rect, const Color& color)
{
    const SDL_Rect sdl_rect = { static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.w), static_cast<int>(rect.h) };
    SDL_SetRenderDrawColor(sdl::g_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(sdl::g_renderer, &sdl_rect);
}
