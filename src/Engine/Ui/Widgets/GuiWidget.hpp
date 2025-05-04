#ifndef ENGINE_GUI_WIDGET_HPP
#define ENGINE_GUI_WIDGET_HPP

#include <memory>

#include "Engine/Events/Event.hpp"
#include "Engine/Graphics/Color.hpp"

class GuiLayout;

/// <summary>
/// Base class for all GUI widgets.
/// By default, it is interactable, visible, not clickable, not disabled and has a unique id.
/// When you set the prefered size, it will be used to compute a size factor so when the window is resized,
/// the widget will be resized accordingly.
/// </summary>
class GuiWidget
{
public:
    GuiWidget();
    virtual ~GuiWidget() = default;
    GuiWidget(const GuiWidget&) = delete;
    GuiWidget& operator=(const GuiWidget&) = delete;
    GuiWidget(const GuiWidget&&) = delete;
    GuiWidget& operator=(const GuiWidget&&) = delete;

    using SP = std::shared_ptr<GuiWidget>;

    virtual void show();
    virtual void hide();
    virtual void set_position(const Vector2f& position);
    virtual void set_size(const Vector2f& size);
    virtual void set_pref_size(const Vector2f& size);
    virtual void set_stretch(const Vector2f& stretch_size) { m_stretch_size = stretch_size; }
    virtual void set_layout(std::shared_ptr<GuiLayout> layout);
    virtual void set_parent_layout(GuiLayout* parent_layout) { m_parent_layout = parent_layout; }
    virtual void set_interactable(const bool interactable) { m_interactable = interactable; }
    virtual void set_disable(const bool disable) { m_disable = disable; }
    [[nodiscard]] int get_id() const { return m_id; }
    [[nodiscard]] virtual const Vector2f& get_position() const { return m_position; }
    [[nodiscard]] virtual const Vector2f& get_size() const { return m_size; }
    [[nodiscard]] virtual const Vector2f& get_strech() const { return m_stretch_size; }
    [[nodiscard]] virtual const Vector2f& get_pref_size_factor() const { return m_pref_size_factor; }
    [[nodiscard]] virtual std::shared_ptr<GuiLayout> get_layout() const { return m_layout; }
    [[nodiscard]] virtual bool contains(const Vector2f& point) const;
    [[nodiscard]] virtual bool is_on_interactable_element(const Vector2f& point) const;
    [[nodiscard]] virtual bool is_on_clickable_element(const Vector2f& point) const;
    [[nodiscard]] virtual bool is_on_disable_element(const Vector2f& point) const;
    [[nodiscard]] virtual bool is_visible() const { return m_visible; }

    virtual void update();
    virtual void on_mouse_move(const Event::MouseMove& event);
    virtual void on_mouse_button_down(const Event::MouseButton& event);
    virtual void on_mouse_button_up(const Event::MouseButton& event);
    virtual void on_key_pressed(const Event::KeyboardButton& event);
    virtual void on_text_input(const Event::TextInput& event);

    virtual void draw();
    virtual void draw_debug();

protected:
    virtual void update_layout();

    Vector2f m_position;
    Vector2f m_size;
    Vector2f m_pref_size_factor = Vector2f::Zero;
    Vector2f m_stretch_size = Vector2f::Zero;
    bool m_interactable = true;
    bool m_visible = true;
    bool m_hovered = false;
    bool m_clickable = false;
    bool m_disable = false;
    std::shared_ptr<GuiLayout> m_layout = nullptr;
    GuiLayout* m_parent_layout = nullptr;
    Color m_debug_color;

private:
    int m_id;

    static int s_id_counter;
};

#endif // ENGINE_GUI_WIDGET_HPP