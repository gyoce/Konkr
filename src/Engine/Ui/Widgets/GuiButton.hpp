#ifndef ENGINE_GUI_BUTTON_HPP
#define ENGINE_GUI_BUTTON_HPP

#include <functional>

#include "Engine/Ui/Widgets/GuiText.hpp"
#include "Engine/Graphics/Font.hpp"

class GuiButton : public GuiWidget
{
public:
    GuiButton();

    void set_size(const Vector2f& size) override;
    void set_position(const Vector2f& position) override;
    virtual void set_on_click_callback(std::function<void()> callback);
    virtual void set_text(std::string text);
    virtual void set_text_padding(const Vector2f& padding) { m_text_padding = padding; }
    virtual void set_background_texture(Texture::SP texture) { m_background_texture = std::move(texture); }
    virtual void set_background_texture_hovered(Texture::SP sp) { m_background_texture_hovered = std::move(sp); }
    virtual void set_key_binding(const Keyboard::Key key) { m_key_binding = key; }

    void on_mouse_button_up(const Event::MouseButton& event) override;
    void on_key_pressed(const Event::KeyboardButton& event) override;

    void draw() override;
    void draw_debug() override;

    using SP = std::shared_ptr<GuiButton>;

protected:
    std::function<void()> m_on_click_callback = nullptr;
    GuiText m_text;
    Vector2f m_text_padding{ 10.0f, 10.0f };
    Texture::SP m_background_texture = nullptr;
    Texture::SP m_background_texture_hovered = nullptr;
    Keyboard::Key m_key_binding = Keyboard::Key::None;
};

#endif // ENGINE_GUI_BUTTON_HPP