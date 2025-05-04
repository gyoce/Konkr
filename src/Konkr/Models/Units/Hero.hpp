#ifndef KONKR_HERO_HPP
#define KONKR_HERO_HPP

#include "Konkr/Models/Unit.hpp"
#include "Konkr/Utils/Constants.hpp"

class Hero final : public Unit
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Hero; }
    [[nodiscard]] int get_level() const override { return constants::hero_level; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::hero_cost_per_turn; }
};

#endif // KONKR_HERO_HPP
