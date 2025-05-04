#ifndef ENGINE_GUI_MANAGER_HPP
#define ENGINE_GUI_MANAGER_HPP

#include "Engine/Events/Event.hpp"
#include "Engine/Ui/Gui.hpp"

class GuiManager
{
public:
    GuiManager() = default;

    void update();
    void draw();

    /// <summary>
    /// Check if a point is on an interactable UI element.
    /// An interactable UI element can be anything if you set_interactable(true) on a widget.
    /// </summary>
    [[nodiscard]] bool is_on_interactable_ui_element(const Vector2f& point) const;

    /// <summary>
    /// Check if a point is on a clickable UI element.
    /// </summary>
    [[nodiscard]] bool is_on_clickable_ui_element(const Vector2f& point) const;

    /// <summary>
    /// Check if a point is on a disable UI element.
    /// </summary>
    [[nodiscard]] bool is_on_disable_ui_element(const Vector2f& point);

    /// <summary>
    /// Dispatch the mouse move event on all UI elements.
    /// </summary>
    void on_mouse_move(const Event::MouseMove& event);

    /// <summary>
    /// Dispatch the mouse button down event on all UI elements.
    /// </summary>
    void on_mouse_button_down(const Event::MouseButton& event);

    /// <summary>
    /// Dispatch the mouse button up event on all UI elements.
    /// </summary>
    /// <param name="event"></param>
    void on_mouse_button_up(const Event::MouseButton& event);

    /// <summary>
    /// Dispatch the window resize event on all UI elements.
    /// </summary>
    void on_window_resize(const Event::WindowResize& event);

    /// <summary>
    /// Dispatch the text input event on all UI elements.
    /// </summary>
    void on_text_input(const Event::TextInput& event);

    /// <summary>
    /// Dispatch the key pressed event on all UI elements.
    /// </summary>
    void on_key_pressed(const Event::KeyboardButton& event);

    /// <summary>
    /// Set the main layout of the GUI.
    /// </summary>
    void set_layout(const GuiLayout::SP& layout);

    static bool debug_mode;

private:
    std::vector<GuiWidget::SP> m_ui_elements{};
    GuiPanel m_main_widget;
};

#endif // ENGINE_GUI_MANAGER_HPP