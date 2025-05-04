#ifndef KONKR_UNIT_HPP
#define KONKR_UNIT_HPP

#include "Konkr/Models/Entity.hpp"
#include "Konkr/Utils/Constants.hpp"

class Unit : public Entity
{
public:
    using SP = std::shared_ptr<Unit>;

    [[nodiscard]] bool is_building() const override { return false; }
    [[nodiscard]] bool is_movable() const override { return !has_moved_in_turn; }
    [[nodiscard]] int get_cost_per_turn() const override { return constants::default_cost_per_turn; }

    bool has_moved_in_turn = false;
};

#endif // KONKR_UNIT_HPP
