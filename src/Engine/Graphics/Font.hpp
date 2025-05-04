#ifndef ENGINE_FONT_HPP
#define ENGINE_FONT_HPP

#include <memory>

#include "Engine/Graphics/Sdl.hpp"
#include "Engine/Graphics/Color.hpp"
#include "Engine/Graphics/Texture.hpp"

class Font
{
public:
    explicit Font(const std::string& path);
    ~Font();
    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;
    Font(Font&&) = delete;
    Font& operator=(Font&&) = delete;

    [[nodiscard]] Texture::SP create_text_texture(const std::string& text, Color color) const;

    using SP = std::shared_ptr<Font>;

private:
    TTF_Font* m_font = nullptr;
};

#endif // ENGINE_FONT_HPP