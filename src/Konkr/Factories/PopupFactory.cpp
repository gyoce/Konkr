#include "PopupFactory.hpp"

#include <utility>

PopupData PopupFactory::create_load_map_error(std::string message)
{
    PopupData data;
    data.message = std::move(message);
    data.text_color = constants::error_text_color;
    data.background_color = constants::error_bg_color;
    data.duration_seconds = constants::infinite_total_duration;
    return data;
}

PopupData PopupFactory::create_player_eliminated(const Player& player)
{
    PopupData data;
    data.message = player.name + " has been eliminated!";
    data.text_color = constants::error_text_color;
    data.background_color = constants::error_bg_color;
    return data;
}