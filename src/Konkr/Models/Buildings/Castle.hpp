#ifndef KONKR_CASTLE_HPP
#define KONKR_CASTLE_HPP

#include "Konkr/Models/Building.hpp"
#include "Konkr/Utils/Constants.hpp"

class Castle final : public Building
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Castle; }
    [[nodiscard]] int get_level() const override { return constants::castle_level; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::castle_cost_per_turn; }
};

#endif // KONKR_CASTLE_HPP
