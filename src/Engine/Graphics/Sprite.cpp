#include "Engine/Graphics/Sprite.hpp"

Sprite::Sprite(Texture::SP texture)
    : m_texture(std::move(texture)), m_size(m_texture->get_size())
{
}

void Sprite::draw() const
{
    m_texture->draw(m_position, m_size);
}