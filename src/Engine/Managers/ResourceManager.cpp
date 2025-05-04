#include "Engine/Managers/ResourceManager.hpp"

#include "Engine/Utils/Logs.hpp"

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager::ResourceManager()
{
    if (s_instance != nullptr)
    {
        logs::error("Only one ResourceManager can exist.");
        throw std::runtime_error("ResourceManager already exists");
    }
    s_instance = this;
}

void ResourceManager::load_sprites(const Texture::SP& sprite_sheet, const std::unordered_map<std::string, std::pair<Recti, bool>>& sprite_rects)
{
    for (const auto& [name, pair] : sprite_rects)
    {
        const auto& [rect, need_antialiasing] = pair;
        if (!need_antialiasing)
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        SDL_Rect sdl_rect = { rect.x, rect.y, rect.w, rect.h };
        SDL_Texture* texture = sdl::extract_texture_from_texture(sprite_sheet->get_texture(), sdl_rect);
        if (texture == nullptr)
        {
            logs::error("Failed to create texture for sprite: {}", name);
            continue;
        }
        m_sprites[name] = std::make_shared<Texture>(texture);
        m_sprites[name]->set_name(name);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    }
}

void ResourceManager::load_font(const std::string& name, const std::string& path)
{
    m_fonts[name] = std::make_shared<Font>(path);
}

void ResourceManager::set_main_font(Font::SP font)
{
    m_main_font = std::move(font);
}

const Texture::SP& ResourceManager::get_sprite(const std::string& name)
{
    if (!s_instance->m_sprites.contains(name))
    {
        logs::error("Sprite not found in sprites : {}", name);
        throw std::runtime_error("Sprite not found");
    }
    return s_instance->m_sprites[name];
}

const Font::SP& ResourceManager::get_font(const std::string& name)
{
    if (!s_instance->m_fonts.contains(name))
    {
        logs::error("Font not found in fonts : {}", name);
        throw std::runtime_error("Font not found");
    }
    return s_instance->m_fonts[name];
}

const Font::SP& ResourceManager::get_main_font()
{
    if (s_instance->m_main_font == nullptr)
    {
        logs::error("Main font not set");
        throw std::runtime_error("Main font not set");
    }
    return s_instance->m_main_font;
}
