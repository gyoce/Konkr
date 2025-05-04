#ifndef KONKR_TOWER_HPP
#define KONKR_TOWER_HPP

#include "Konkr/Models/Building.hpp"
#include "Konkr/Utils/Constants.hpp"

class Tower final : public Building
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Tower; }
    [[nodiscard]] int get_level() const override { return constants::tower_level; }
    [[nodiscard]] int get_price() const override { return constants::tower_price; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::tower_cost_per_turn; }
};

#endif // KONKR_TOWER_HPP
