#ifndef KONKR_SELECTABLE_TEXTS_HPP
#define KONKR_SELECTABLE_TEXTS_HPP

#include "Engine/Ui/Gui.hpp"

#include <vector>
#include <string>
#include <functional>

class SelectableOptions final : public GuiPanel
{
public:
    SelectableOptions();

    void set_title(const std::string& title) const;
    void set_options(const std::vector<std::string>& options);
    void set_option_selected_callback(std::function<void(int)> callback) { m_on_option_selected = std::move(callback); }
    void set_selected(int index);

    using SP = std::shared_ptr<SelectableOptions>;

private:
    void on_select_left();
    void on_select_right();

    std::vector<GuiText::SP> m_selectable_options;
    std::function<void(int)> m_on_option_selected = nullptr;
    int m_current_option = 0;
    GuiText::SP m_text_tile;
    GuiHorizontalLayout::SP m_options_layout;
};

#endif // KONKR_SELECTABLE_TEXTS_HPP