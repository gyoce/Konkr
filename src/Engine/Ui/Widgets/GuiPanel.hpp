#ifndef ENGINE_GUI_PANEL_HPP
#define ENGINE_GUI_PANEL_HPP

#include "Engine/Ui/Widgets/GuiWidget.hpp"
#include "Engine/Graphics/Texture.hpp"

/// <summary>
/// Represents a panel in the Gui i.e. a background for other widgets.
/// By default, is not interactable.
/// </summary>
class GuiPanel : public GuiWidget
{
public:
    GuiPanel();

    virtual void set_background_texture(Texture::SP texture) { m_background_texture = std::move(texture); }
    virtual void set_background_color(const Color& color) { m_background_color = color; }

    void draw() override;
    void draw_debug() override;

    using SP = std::shared_ptr<GuiPanel>;

protected:
    Texture::SP m_background_texture = nullptr;
    Color m_background_color = Color::None;
};

#endif // ENGINE_GUI_PANEL_HPP