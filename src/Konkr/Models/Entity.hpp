#ifndef KONKR_ENTITY_HPP
#define KONKR_ENTITY_HPP

#include "Konkr/Hex/HexEnums.hpp"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(Entity&&) = delete;

    using SP = std::shared_ptr<Entity>;

    [[nodiscard]] virtual HexEntity get_decoration() const { return HexEntity::None; }
    [[nodiscard]] virtual bool is_movable() const = 0;
    [[nodiscard]] virtual bool is_building() const = 0;
    [[nodiscard]] virtual int get_level() const = 0;
    [[nodiscard]] virtual int get_price() const { return 0; }
    [[nodiscard]] virtual int get_cost_per_turn() const = 0;

    bool bouncing = false;
    float bounce_offset = 0.0f;
    float bounce_accumulator = 0.0f;
};

#endif // KONKR_ENTITY_HPP
