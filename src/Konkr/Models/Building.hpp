#ifndef KONKR_BUILDING_HPP
#define KONKR_BUILDING_HPP

#include "Konkr/Models/Entity.hpp"

class Building : public Entity
{
public:
    using SP = std::shared_ptr<Building>;

    [[nodiscard]] bool is_movable() const override { return false; }
    [[nodiscard]] bool is_building() const override { return true; }
};

#endif // KONKR_BUILDING_HPP
