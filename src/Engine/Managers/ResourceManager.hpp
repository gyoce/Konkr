#ifndef ENGINE_RESOURCE_MANAGER_HPP
#define ENGINE_RESOURCE_MANAGER_HPP

#include "Engine/Graphics/Texture.hpp"
#include "Engine/Graphics/Font.hpp"

#include <unordered_map>

class ResourceManager
{
public:
    ResourceManager();

    /// <summary>
    /// Get a sprite by its name.
    /// It has to be loaded before with the load_sprites() method.
    /// </summary>
    static const Texture::SP& get_sprite(const std::string& name);

    /// <summary>
    /// Get a font by its name.
    /// It has to be loaded before with the load_font() method.
    /// </summary>
    static const Font::SP& get_font(const std::string& name);

    /// <summary>
    /// Get the main font.
    /// It has to be set with the set_main_font() method.
    /// </summary>
    static const Font::SP& get_main_font();

    /// <summary>
    /// Load sprites from a sprite sheet.
    /// The parameters "sprite_sheets" contains the name of the sprite as key and a pair of Recti and bool as value.
    /// The bool indicates if the sprite needs antialiasing or not.
    /// </summary>
    void load_sprites(const Texture::SP& sprite_sheet, const std::unordered_map<std::string, std::pair<Recti, bool>>& sprite_rects);

    /// <summary>
    /// Load a font from a file, the font must be TTF.
    /// </summary>
    void load_font(const std::string& name, const std::string& path);

    /// <summary>
    /// Set the main font that will be used for the GUI.
    /// </summary>
    void set_main_font(Font::SP font);

    using UP = std::unique_ptr<ResourceManager>;

private:
    std::unordered_map<std::string, Texture::SP> m_sprites{};
    std::unordered_map<std::string, Font::SP> m_fonts{};
    Font::SP m_main_font = nullptr;

    static ResourceManager* s_instance;
};

#endif // ENGINE_RESOURCE_MANAGER_HPP