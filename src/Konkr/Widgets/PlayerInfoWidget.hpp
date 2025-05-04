#ifndef KONKR_PLAYER_INFO_WIDGET_HPP
#define KONKR_PLAYER_INFO_WIDGET_HPP

#include <functional>

#include "Engine/Ui/Gui.hpp"
#include "Konkr/Hex/HexEnums.hpp"
#include "Konkr/Models/Player.hpp"

class PlayerInfoWidget final : public GuiPanel
{
public:
    PlayerInfoWidget();

    /// <summary>
    /// Set the player information on the ui widget. 
    /// </summary>
    void set_player_info(const Player& player, const std::vector<HexEntity>& not_buyable_entities, bool undo_active);

    /// <summary>
    /// Set the callback for when a unit is selected i.e. when the user left-click on a unit button.
    /// </summary>
    void set_on_unit_selected_callback(std::function<void(HexEntity)> callback) { m_on_unit_selected_callback = std::move(callback); }

    /// <summary>
    /// Set the callback for when the user clicks on the end turn button.
    /// </summary>
    void set_end_turn_callback(std::function<void()> callback) { m_end_turn_callback = std::move(callback); }

    void add_undo_callback(std::function<void()> callback) { m_undo_callbacks.push_back(std::move(callback)); }

    using SP = std::shared_ptr<PlayerInfoWidget>;

private:
    /// <summary>
    /// Reset the "unit" buttons i.e. the buttons to buy units, set them not disabled and set the correct texture.
    /// </summary>
    void reset_unit_buttons(const Player& player) const;

    /// <summary>
    /// For every unit that the user can't buy set the button to disabled and set the correct texture.
    /// </summary>
    void update_buyable_entities_button(const Player& player, const std::vector<HexEntity>& not_buyable_entities) const;

    void select_unit_type(HexEntity type) const;
    void send_end_turn_callback() const;
    void send_undo_callback() const;

    GuiButton::SP m_undo_button;

    GuiText::SP m_name_label;
    GuiText::SP m_total_money_label;
    GuiText::SP m_earned_money_label;
    GuiImage::SP m_earned_money_img;

    std::function<void(HexEntity)> m_on_unit_selected_callback = nullptr;
    std::function<void()> m_end_turn_callback = nullptr;
    std::vector<std::function<void()>> m_undo_callbacks;

    GuiButton::SP m_villager_button;
    GuiButton::SP m_soldier_button;
    GuiButton::SP m_knight_button;
    GuiButton::SP m_tower_button;
};

#endif // KONKR_PLAYER_INFO_WIDGET_HPP
