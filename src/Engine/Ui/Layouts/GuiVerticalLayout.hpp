#ifndef ENGINE_GUI_VERTICAL_LAYOUT_HPP
#define ENGINE_GUI_VERTICAL_LAYOUT_HPP

#include "Engine/Ui/Layouts/GuiLayout.hpp"
#include "Engine/Ui/GuiEnums.hpp"

class GuiVerticalLayout : public GuiLayout
{
public:
    void update_layout() override;

    void set_horizontal_align(const Horizontal align) { m_horizontal_align = align; }
    void set_padding_between_items(const Vector2f& padding) { m_padding_between_items = padding; }
    void set_vertical_start(const Vertical align) { m_vertical_start = align; }
    void set_offset_start_items(const Vector2f& offset) { m_offset_start_items = offset; }

    using SP = std::shared_ptr<GuiVerticalLayout>;

protected:
    void update_widgets_position() const;
    void update_widgets_position_top() const;
    void update_widgets_position_center() const;
    void update_widgets_position_bottom() const;
    [[nodiscard]] float get_x_pos_of_widget(const GuiWidget::SP& widget) const;
    [[nodiscard]] float compute_total_widgets_height_with_padding() const;

    Horizontal m_horizontal_align = Horizontal::Center;
    Vertical m_vertical_start = Vertical::Center;
    Vector2f m_padding_between_items = Vector2f::Zero;
    Vector2f m_offset_start_items = Vector2f::Zero;
};

#endif // ENGINE_GUI_VERTICAL_LAYOUT_HPP