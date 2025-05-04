#ifndef ENGINE_SPRITE_HPP
#define ENGINE_SPRITE_HPP

#include "Engine/Graphics/Texture.hpp"

class Sprite
{
public:
    Sprite() = default;
    explicit Sprite(Texture::SP texture);
    virtual ~Sprite() = default;
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
    Sprite(Sprite&&) = delete;
    Sprite& operator=(Sprite&&) = delete;

    [[nodiscard]] virtual const Vector2f& get_size() const { return m_size; }
    [[nodiscard]] virtual const Vector2f& get_position() const { return m_position; }
    [[nodiscard]] virtual const Texture::SP& get_texture() const { return m_texture; }
    virtual void set_position(const Vector2f& position) { m_position = position; }
    virtual void set_size(const Vector2f& size) { m_size = size; }

    virtual void draw() const;

    using SP = std::shared_ptr<Sprite>;
    using UP = std::unique_ptr<Sprite>;

protected:
    Texture::SP m_texture;
    Vector2f m_size;
    Vector2f m_position;
};

#endif // ENGINE_SPRITE_HPP