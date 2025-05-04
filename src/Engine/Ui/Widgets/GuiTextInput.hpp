#ifndef ENGINE_GUI_TEXT_INPUT_HPP
#define ENGINE_GUI_TEXT_INPUT_HPP

#include <string>

#include "Engine/Ui/Widgets/GuiText.hpp"
#include "Engine/Ui/Widgets/GuiWidget.hpp"
#include "Engine/Utils/Timer.hpp"

class GuiTextInput : public GuiWidget
{
public:
    GuiTextInput();

    using SP = std::shared_ptr<GuiTextInput>;

    void set_size(const Vector2f& size) override;
    void set_position(const Vector2f& position) override;
    void draw() override;
    void draw_debug() override;

    void update() override;
    void on_mouse_button_down(const Event::MouseButton& event) override;
    void on_key_pressed(const Event::KeyboardButton& event) override;
    void on_text_input(const Event::TextInput& event) override;

    virtual void set_background_color(const Color color) { m_background_color = color; }
    virtual void set_text_padding(const Vector2f& padding) { m_text_padding = padding; }

    [[nodiscard]] const std::string& get_text() const { return m_text; }

protected:
    void update_text_and_caret();

    Color m_background_color = Color::None;
    Rectf m_caret_rect{0, 0, 5, 0};
    Vector2f m_text_padding{ 10, 10 };
    GuiText m_text_widget;
    Timer m_caret_timer;
    bool m_focus = false;
    bool m_need_caret_draw = false;
    std::string m_text;
};

#endif // ENGINE_GUI_TEXT_INPUT_HPP