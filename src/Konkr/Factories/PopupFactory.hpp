#ifndef KONKR_POPUPFACTORY_HPP
#define KONKR_POPUPFACTORY_HPP

#include "Konkr/Widgets/PopupWidget.hpp"
#include "Konkr/Models/Player.hpp"

class PopupFactory
{
public:
    static PopupData create_load_map_error(std::string message);
    static PopupData create_player_eliminated(const Player& player);
};

#endif // KONKR_POPUPFACTORY_HPP
