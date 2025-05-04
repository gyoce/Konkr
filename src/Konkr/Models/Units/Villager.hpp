#ifndef KONKR_VILLAGER_HPP
#define KONKR_VILLAGER_HPP

#include "Konkr/Models/Unit.hpp"
#include "Konkr/Utils/Constants.hpp"

class Villager final : public Unit
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Villager; }
    [[nodiscard]] int get_level() const override { return constants::villager_level; }
    [[nodiscard]] int get_price() const override { return constants::villager_price; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::villager_cost_per_turn; }

    using SP = std::shared_ptr<Villager>;
};

#endif // KONKR_VILLAGER_HPP
