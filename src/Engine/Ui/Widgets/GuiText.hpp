#ifndef ENGINE_GUI_TEXT_HPP
#define ENGINE_GUI_TEXT_HPP

#include <string>

#include "Engine/Ui/Widgets/GuiWidget.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Engine/Graphics/Color.hpp"
#include "Engine/Ui/GuiEnums.hpp"

class GuiText : public GuiWidget
{
public:
    GuiText();

    using SP = std::shared_ptr<GuiText>;

    void set_size(const Vector2f& size) override;
    void set_position(const Vector2f& position) override;
    virtual void set_text(std::string text, bool refresh_parent = false);
    virtual void set_text_color(Color color);
    virtual void set_horizontal_align(const Horizontal horizontal) { m_horizontal_start = horizontal; }
    [[nodiscard]] virtual const Vector2f& get_text_size() { return m_text_size; }

    void draw() override;
    void draw_debug() override;

protected:
    virtual void compute_text_size();
    virtual void compute_text_position();

    std::string m_text;
    Vector2f m_text_size;
    Vector2f m_text_position;
    Color m_text_color = Color::White;
    Texture::SP m_text_texture = nullptr;
    Horizontal m_horizontal_start = Horizontal::Center;
};

#endif // ENGINE_GUI_TEXT_HPP