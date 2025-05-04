#ifndef KONKR_KNIGHT_HPP
#define KONKR_KNIGHT_HPP

#include "Konkr/Models/Unit.hpp"
#include "Konkr/Utils/Constants.hpp"

class Knight final : public Unit
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Knight; }
    [[nodiscard]] int get_level() const override { return constants::knight_level; }
    [[nodiscard]] int get_price() const override { return constants::knight_price; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::knight_cost_per_turn; }
};

#endif // KONKR_KNIGHT_HPP
