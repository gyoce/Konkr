#ifndef ENGINE_TEXTURE_HPP
#define ENGINE_TEXTURE_HPP

#include <memory>
#include <string>

#include "Engine/Graphics/Sdl.hpp"
#include "Engine/Math/Math.hpp"

class Texture
{
public:
    explicit Texture(SDL_Texture* texture);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(Texture&&) = delete;

    void set_name(std::string name) { m_name = std::move(name); }
    [[nodiscard]] const Vector2f& get_size() const { return m_size; }
    [[nodiscard]] SDL_Texture* get_texture() const { return m_texture; }

    void draw(const Vector2f& position, const Vector2f& size) const;
    void draw(const Vector2f& position) const;

    using SP = std::shared_ptr<Texture>;

    static SP load_image(const std::string& path);

private:
    SDL_Texture* m_texture;
    std::string m_name;
    Vector2f m_size;
};

#endif // ENGINE_TEXTURE_HPP