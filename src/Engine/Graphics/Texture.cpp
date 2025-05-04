#include "Engine/Graphics/Texture.hpp"

#include "Engine/Utils/Logs.hpp"

Texture::Texture(SDL_Texture* texture)
    : m_texture(texture)
{
    int w, h;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);
    m_size.x = static_cast<float>(w);
    m_size.y = static_cast<float>(h);
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

void Texture::draw(const Vector2f& position, const Vector2f& size) const
{
    const SDL_Rect dst_rect {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderCopy(sdl::g_renderer, m_texture, nullptr, &dst_rect);
}

void Texture::draw(const Vector2f& position) const
{
    const SDL_Rect dst_rect {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(m_size.x), static_cast<int>(m_size.y)};
    SDL_RenderCopy(sdl::g_renderer, m_texture, nullptr, &dst_rect);
}

Texture::SP Texture::load_image(const std::string& path)
{
    SDL_Texture* texture = IMG_LoadTexture(sdl::g_renderer, path.c_str());
    if (texture == nullptr)
    {
        logs::error("IMG_LoadTexture failed: {}", IMG_GetError());
        return nullptr;
    }
    return std::make_shared<Texture>(texture);
}
