#ifndef ENGINE_GUI_ANCHOR_LAYOUT_HPP
#define ENGINE_GUI_ANCHOR_LAYOUT_HPP

#include <unordered_map>

#include "Engine/Ui/GuiEnums.hpp"
#include "Engine/Ui/Layouts/GuiLayout.hpp"

class GuiAnchorLayout : public GuiLayout
{
public:
    void update_layout() override;

    using SP = std::shared_ptr<GuiAnchorLayout>;

    void add_widget(const GuiWidget::SP& widget) override;
    virtual void add_widget(const GuiWidget::SP& widget, Horizontal horizontal_anchor, Vertical vertical_anchor);
    void add_layout(const GuiLayout::SP& layout) override;
    virtual void add_layout(const GuiLayout::SP& layout, Horizontal horizontal_anchor, Vertical vertical_anchor);

    virtual void set_anchor(const GuiWidget::SP& widget, Horizontal horizontal_anchor, Vertical vertical_anchor);
    virtual void set_anchor(const GuiLayout::SP& layout, Horizontal horizontal_anchor, Vertical vertical_anchor);
    virtual void set_offset_start_items(const Vector2f& offset) { m_offset_start_items = offset; }

protected:
    void update_widgets_position() const;

    std::unordered_map<int, std::pair<Horizontal, Vertical>> m_widget_anchors;
    Vector2f m_offset_start_items = Vector2f::Zero;
};

#endif // ENGINE_GUI_ANCHOR_LAYOUT_HPP