#include "Engine/Graphics/Font.hpp"

#include "Engine/Utils/Logs.hpp"

Font::Font(const std::string& path)
{
    m_font = TTF_OpenFont(path.c_str(), 96);
    TTF_SetFontHinting(m_font, TTF_HINTING_LIGHT);
    if (m_font == nullptr)
    {
        logs::error("TTF_OpenFont failed: {}", TTF_GetError());
        return;
    }
}

Font::~Font()
{
    TTF_CloseFont(m_font);
}

Texture::SP Font::create_text_texture(const std::string& text, const Color color) const
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font, text.c_str(), SDL_Color { color.r, color.g, color.b, color.a });
    if (surface == nullptr)
    {
        logs::error("TTF_RenderUTF8_Blended failed: {}", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl::g_renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        logs::error("SDL_CreateTextureFromSurface failed: {}", SDL_GetError());
        return nullptr;
    }
    return std::make_shared<Texture>(texture);
}
