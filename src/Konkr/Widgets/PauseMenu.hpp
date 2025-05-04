#ifndef KONKR_PAUSE_MENU_HPP
#define KONKR_PAUSE_MENU_HPP

#include "Engine/Ui/Gui.hpp"

class PauseMenu final : public GuiPanel
{
public:
    PauseMenu();

    void toggle_pause_menu();
    void set_associated_widget(GuiWidget::SP widget) { m_associated_widget = std::move(widget); }

    using SP = std::shared_ptr<PauseMenu>;

private:
    bool m_pause = false;
    GuiWidget::SP m_associated_widget = nullptr;
};

#endif // KONKR_PAUSE_MENU_HPP