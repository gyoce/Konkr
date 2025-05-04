#ifndef KONKR_GAME_MANAGER_HPP
#define KONKR_GAME_MANAGER_HPP

#include <stack>
#include <set>

#include "Engine/Scenes/SceneObject.hpp"
#include "Konkr/Hex/Map.hpp"
#include "Konkr/Models/Player.hpp"
#include "Konkr/Widgets/EndGameWidget.hpp"
#include "Konkr/Widgets/PlayerInfoWidget.hpp"
#include "Konkr/Widgets/PopupWidget.hpp"

struct Action
{
    std::optional<HexTile> from;
    HexTile to;
    Entity::SP moving_entity;
    std::optional<Entity::SP> previous_entity;
    int previous_player_to;
    int cost;
    std::vector<HexTile> previous_hex_tiles_states;
};

class GameManager final : public SceneObject
{
public:
    explicit GameManager(Map::SP map);

    void on_enter() override;

    /// <summary>
    /// Get all the possible hex moves for the given entity that may start from the "from" hex.
    /// </summary>
    [[nodiscard]] std::vector<HexTile::REF> get_possible_hex_moves(const Entity::SP& moving_entity, const std::optional<HexTile::REF>& from) const;

    /// <summary>
    /// Move a "decoration" i.e. a unit from one hex to another.
    /// </summary>
    void move_decoration(HexTile& from, HexTile& to);

    /// <summary>
    /// Place a new entity on the "to" hex.
    /// </summary>
    void place_unit(HexTile& to, const HexEntity& entity_type);

    [[nodiscard]] bool can_move_decoration(const HexTile& hex) const;

    void undo_last_action();

    [[nodiscard]] int get_current_player_id() const { return player_playing().id; }
    void set_player_ui(PlayerInfoWidget::SP ui);
    void set_popup_ui(PopupWidget::SP ui) { m_popup_ui = std::move(ui); }
    void set_endgame_ui(EndGameWidget::SP ui) { m_endgame_ui = std::move(ui); }
    void set_end_turn_callback(std::function<void()> callback) { m_end_turn_callback = std::move(callback); }
    void set_undo_callback(std::function<void()> callback) { m_undo_callback = std::move(callback); }

    using SP = std::shared_ptr<GameManager>;

private:
    [[nodiscard]] Player& player_playing() { return m_players[m_index_player_playing]; }
    [[nodiscard]] const Player& player_playing() const { return m_players[m_index_player_playing]; }

    [[nodiscard]] bool path_exist_between(const HexTile& from, const HexTile& to, int player) const;

    /// <summary>
    /// Compute the safe level and the fences of all hexes i.e. check if the hexes are safe or not and in which direction they are not.
    /// </summary>
    void compute_safe_level_and_fences() const;

    /// <summary>
    /// This method will reset the tag "safe" of every hex to false and the safe level to 0.
    /// If the hex has a building it will be tagged "safe" and set the appropriate safe level.
    /// </summary>
    void reset_hexes_safety() const;

    /// <summary>
    /// This method will compute the safety of the entities i.e. set the tag "safe" of every hex that is a neighbor of a building to true
    /// if the entity is owned by the same player and set the appropriate safe level.
    /// </summary>
    void compute_entities_safety() const;

    /// <summary>
    /// This method will compute the fences for every hex that is tagged "safe" i.e. check for every direction if the neighbor is safe or not.
    /// </summary>
    void compute_fences() const;

    /// <summary>
    /// Insert territories that are linked to a castle in player class.
    /// </summary>
    void insert_territories_linked_to_castle(Player &player) const;

    /// <summary>
    /// Initialize territories list for each player.
    /// </summary>
    void init_players_active_territories();

    /// <summary>
    /// This method will compute the logic when a move occurs.
    /// </summary>
    void apply_move_logic(const Entity::SP& entity, HexTile& to, std::optional<HexTile::REF> from = std::nullopt);

    /// <summary>
    /// Search inside the map and count how many different players are present.
    /// </summary>
    [[nodiscard]] std::set<int> compute_number_of_player() const;

    /// <summary>
    /// Create the player list and set the first player to play.
    /// </summary>
    void setup_players();

    /// <summary>
    /// Send data to the player UI to update the information about the current player.
    /// </summary>
    void update_player_ui();

    /// <summary>
    /// Compute the money earned by the player.
    /// Each tile owned by the player will give him 1 money.
    /// Each entity owned by the player will cost some money.
    /// If there is a bandit on the tile, it doesn't give money.
    /// </summary>
    [[nodiscard]] int compute_player_earn() const;

    /// <summary>
    /// Check if a merge between two units is possible and make it.
    /// </summary>
    [[nodiscard]] Entity::SP check_and_apply_merge(const Entity::SP& entity, const HexTile &to) const;

    /// <summary>
    /// Check if there is a cut between 'active' territories of a player and if it is the case, make territory
    /// neutral and create bandits where there is a unit.
    /// </summary>
    void check_cut_territory(int previous_owner);

    /// <summary>
    /// Check if the player has at least one castle left.
    /// </summary>
    [[nodiscard]] bool check_player_dead(int player_id) const;

    /// <summary>
    /// Basic condition to check if a merge is possible.
    /// </summary>
    static bool is_merge_possible(const Entity::SP& moving_entity, const HexTile& hex);

    /// <summary>
    /// Get a player by his id.
    /// </summary>
    Player& get_player_by_id(int id);

    void save_action_to_stack(const HexTile& to, const Entity::SP &moving_entity, const std::optional<HexTile>& from = std::nullopt);

    /// <summary>
    /// Check for all player if they can afford the salary of their units, if not units become bandits.
    /// </summary>
    void check_if_player_can_afford_units_salary();

    /// <summary>
    /// Reset the value has_moved_in_turn to false for all units of the current player.
    /// </summary>
    void reset_units_state_of_current_player() const;

    /// <summary>
    /// Move randomly bandits at every new round.
    /// Increment round counter and reset turn counter.
    /// </summary>
    void move_bandit_if_new_round();

    void start_game();
    void end_turn();

    struct QueueItem
    {
        HexTile tile;
        int priority;

        bool operator<(const QueueItem& other) const
        {
            return priority > other.priority;
        }
    };

    Map::SP m_map;
    PlayerInfoWidget::SP m_player_ui;
    PopupWidget::SP m_popup_ui;
    EndGameWidget::SP m_endgame_ui;
    std::array<Player, 4> m_players{};
    int m_index_player_playing { -1 };
    std::stack<Action> m_actions;
    int m_round_number{ 1 };
    int m_number_of_turn{ 0 };
    std::function<void()> m_end_turn_callback = nullptr;
    std::function<void()> m_undo_callback = nullptr;
    std::vector<HexTile> m_modified_tiles;
    std::vector<Player::REF> m_ranking;
};

#endif // KONKR_GAME_MANAGER_HPP