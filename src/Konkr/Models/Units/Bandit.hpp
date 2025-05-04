#ifndef KONKR_BANDIT_HPP
#define KONKR_BANDIT_HPP

#include "Konkr/Models/Unit.hpp"
#include "Konkr/Utils/Constants.hpp"

class Bandit final : public Unit
{
public:
    [[nodiscard]] HexEntity get_decoration() const override { return HexEntity::Bandit; }
    [[nodiscard]] int get_level() const override { return constants::bandit_level; }
    [[nodiscard]] bool is_movable() const override { return false; }

    using SP = std::shared_ptr<Bandit>;
};

#endif // KONKR_BANDIT_HPP
