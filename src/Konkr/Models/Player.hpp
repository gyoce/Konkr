#ifndef KONKR_PLAYER_HPP
#define KONKR_PLAYER_HPP

#include <string>
#include <memory>
#include <unordered_set>

#include "Engine/Graphics/Color.hpp"
#include "Konkr/Hex/HexTile.hpp"

inline bool operator==(const HexTile::REF& ref1, const HexTile::REF& ref2)
{
    return ref1.get() == ref2.get();
}

class Player
{
public:
    Player() = default;
    Player(const int id, std::string name, const Color& color) : id(id), name(std::move(name)), color(color) {  }

    using SP = std::shared_ptr<Player>;
    using REF = std::reference_wrapper<Player>;

    struct Hash
    {
        size_t operator()(const HexTile::REF& hex) const
        {
            return std::hash<int>()(hex.get().q()) ^ std::hash<int>()(hex.get().r()) ^ std::hash<int>()(hex.get().s());
        }
    };

    int id;
    std::string name;
    Color color;
    int money{ 100 };
    int money_per_turn{ 0 };
    std::unordered_set<HexTile::REF, Hash> territories;
    bool dead{ false };
};

#endif // KONKR_PLAYER_HPP