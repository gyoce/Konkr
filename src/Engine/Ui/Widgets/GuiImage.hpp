#ifndef ENGINE_GUI_IMAGE_HPP
#define ENGINE_GUI_IMAGE_HPP

#include "Engine/Ui/Widgets/GuiWidget.hpp"
#include "Engine/Graphics/Texture.hpp"

class GuiImage : public GuiWidget
{
public:
    void set_image(Texture::SP texture) { m_texture = std::move(texture); }

    void draw() override;
    void draw_debug() override;

    using SP = std::shared_ptr<GuiImage>;

protected:
    Texture::SP m_texture = nullptr;
};

#endif // ENGINE_GUI_IMAGE_HPP