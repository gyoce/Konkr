#ifndef ENGINE_GRID_LAYOUT_HPP
#define ENGINE_GRID_LAYOUT_HPP

#include <unordered_map>

#include "Engine/Ui/Layouts/GuiLayout.hpp"

class GuiGridLayout : public GuiLayout
{
public:
    void update_layout() override;

    using SP = std::shared_ptr<GuiGridLayout>;

    void add_widget(const GuiWidget::SP& widget) override;
    virtual void add_widget(const GuiWidget::SP& widget, int row, int column);
    void add_layout(const GuiLayout::SP& layout) override;
    virtual void add_layout(const GuiLayout::SP& layout, int row, int column);

    void set_widget_pos(const GuiWidget::SP& widget, int row, int column);
    void set_layout_pos(const GuiLayout::SP& layout, int row, int column);
    void set_grid(int rows, int columns);
    void set_padding_items(const Vector2f& padding) { m_padding_items = padding; }

protected:
    void update_widgets_size() override;
    void update_widgets_position();

    int m_columns = 1;
    int m_rows = 1;
    float m_cell_width = 0.0f;
    float m_cell_height = 0.0f;
    Vector2f m_padding_items = { 5, 5 };

    std::unordered_map<int, std::pair<int, int>> m_widget_positions{};
};

#endif // ENGINE_GRID_LAYOUT_HPP