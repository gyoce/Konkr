#ifndef ENGINE_GUI_LAYOUT_HPP
#define ENGINE_GUI_LAYOUT_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include <ranges>

#include "Engine/Events/Event.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Ui/Widgets/GuiWidget.hpp"

/// <summary>
/// Base class for all GUI layouts.
/// A layout is a specific container that can contain other widgets or layouts.
/// </summary>
class GuiLayout
{
public:
    GuiLayout() = default;
    virtual ~GuiLayout() = default;
    GuiLayout(const GuiLayout&) = delete;
    GuiLayout& operator=(const GuiLayout&) = delete;
    GuiLayout(const GuiLayout&&) = delete;
    GuiLayout& operator=(const GuiLayout&&) = delete;

    using SP = std::shared_ptr<GuiLayout>;

    virtual void update();
    virtual void draw();
    virtual void draw_debug();

    virtual void set_stretch(const Vector2f& stretch) { m_strech = stretch; }
    virtual void set_pref_size(const Vector2f& size) { m_pref_size = size; }
    virtual void set_parent_widget(GuiWidget* widget) { m_parent_widget = widget; }
    virtual void set_interactable(const bool interactable) { m_interactable = interactable; }
    virtual void set_background_color(const Color& background_color) { m_background_color = background_color; }
    [[nodiscard]] virtual const Vector2f& get_stretch() const { return m_strech; }
    [[nodiscard]] virtual const Vector2f& get_pref_size() const { return m_pref_size; }
    [[nodiscard]] virtual const Color& get_background_color() const { return m_background_color; }
    [[nodiscard]] virtual bool is_interactable() const { return m_interactable; }

    virtual void clear();
    virtual void add_widget(const GuiWidget::SP& widget);
    virtual void add_layout(const SP& layout);
    virtual bool is_on_interactable_element(const Vector2f& point);
    virtual bool is_on_clickable_element(const Vector2f& point);
    virtual bool is_on_disable_element(const Vector2f& point);

    virtual void on_mouse_move(const Event::MouseMove& event);
    virtual void on_mouse_button_down(const Event::MouseButton& event);
    virtual void on_mouse_button_up(const Event::MouseButton& event);
    virtual void on_key_pressed(const Event::KeyboardButton& event);
    virtual void on_text_input(const Event::TextInput& event);

    virtual void update_layout() = 0;

protected:
    [[nodiscard]] std::vector<GuiWidget::SP> visible_widgets() const
    {
        // Here we create a copy of the visible widgets because the tag visible of a widget can be changed while looping through the widgets.
        std::vector<GuiWidget::SP> visible_widgets;
        std::ranges::copy_if(m_widgets, std::back_inserter(visible_widgets), [](const GuiWidget::SP& widget) { return widget->is_visible(); });
        return visible_widgets;
    }
    virtual void update_widgets_size();

    std::vector<GuiWidget::SP> m_widgets{};
    Vector2f m_strech = Vector2f::Zero;
    Vector2f m_pref_size = Vector2f::Zero;
    bool m_interactable = false;
    Color m_background_color = Color::None;
    GuiWidget* m_parent_widget = nullptr;
};

#endif // ENGINE_GUI_LAYOUT_HPP