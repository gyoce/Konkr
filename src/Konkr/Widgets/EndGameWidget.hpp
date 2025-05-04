#ifndef KONKR_END_GAME_WIDGET_H
#define KONKR_END_GAME_WIDGET_H

#include "Engine/Ui/Gui.hpp"
#include "Konkr/Models/Player.hpp"

class EndGameWidget final : public GuiPanel
{
public:
    EndGameWidget();

    void set_associated_widget(GuiWidget::SP widget) { m_associated_widget = std::move(widget); }

    void set_ranking(const std::vector<Player::REF>& ranking);

    using SP = std::shared_ptr<EndGameWidget>;

private:
    GuiWidget::SP m_associated_widget = nullptr;
    std::vector<GuiText::SP> m_players_name;
};

#endif // KONKR_END_GAME_WIDGET_H
