#ifndef ENGINE_GUI_HORIZONTAL_LAYOUT_HPP
#define ENGINE_GUI_HORIZONTAL_LAYOUT_HPP

#include "Engine/Ui/Layouts/GuiLayout.hpp"
#include "Engine/Ui/GuiEnums.hpp"

class GuiHorizontalLayout : public GuiLayout
{
public:
    void update_layout() override;

    using SP = std::shared_ptr<GuiHorizontalLayout>;

    void add_widget(const GuiWidget::SP& widget) override;
    virtual void add_widget(const GuiWidget::SP& widget, size_t index);
    void add_layout(const GuiLayout::SP& layout) override;
    virtual void add_layout(const SP& layout, size_t index);

    void set_vertical_align(const Vertical align) { m_vertical_align = align; }
    void set_padding_between_items(const Vector2f& padding) { m_padding_between_items = padding; }
    void set_horizontal_start(const Horizontal align) { m_horizontal_start = align; }
    void set_offset_start_items(const Vector2f& offset) { m_offset_start_items = offset; }

protected:
    void update_widgets_position() const;
    void update_widgets_position_left() const;
    void update_widgets_position_center() const;
    void update_widgets_position_right() const;
    [[nodiscard]] float get_y_pos_of_widget(const GuiWidget::SP& widget) const;
    [[nodiscard]] float compute_total_children_width_with_padding() const;

    Vertical m_vertical_align = Vertical::Center;
    Horizontal m_horizontal_start = Horizontal::Center;
    Vector2f m_padding_between_items = Vector2f::Zero;
    Vector2f m_offset_start_items = Vector2f::Zero;
};

#endif // ENGINE_GUI_HORIZONTAL_LAYOUT_HPP