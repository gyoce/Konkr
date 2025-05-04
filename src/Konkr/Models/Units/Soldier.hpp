#ifndef KONKR_SOLDIER_HPP
#define KONKR_SOLDIER_HPP

#include "Konkr/Models/Unit.hpp"
#include "Konkr/Utils/Constants.hpp"

class Soldier final : public Unit
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Soldier; }
    [[nodiscard]] int get_level() const override { return constants::soldier_level; }
    [[nodiscard]] int get_price() const override { return constants::soldier_price; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::soldier_cost_per_turn; }
};

#endif // KONKR_SOLDIER_HPP
