#include "Konkr/Managers/GameManager.hpp"

#include "Engine/Managers/SceneManager.hpp"

#include <queue>
#include <utility>

#include "Engine/Utils/Random.hpp"
#include "Engine/Utils/Utils.hpp"
#include "Konkr/Models/Player.hpp"
#include "Konkr/Models/Buildings/Tower.hpp"
#include "Konkr/Models/Units/Hero.hpp"
#include "Konkr/Models/Units/Knight.hpp"
#include "Konkr/Models/Units/Soldier.hpp"
#include "Konkr/Models/Units/Villager.hpp"
#include "Konkr/Models/Units/Bandit.hpp"
#include "Konkr/Factories/PopupFactory.hpp"

GameManager::GameManager(Map::SP map)
    : m_map(std::move(map))
{ }

void GameManager::on_enter()
{
    compute_safe_level_and_fences();
    start_game();
}

std::vector<HexTile::REF> GameManager::get_possible_hex_moves(const Entity::SP& moving_entity, const std::optional<HexTile::REF>& from) const
{
    HexContainer& hexes = m_map->get_map();

    // First, get all the hexes that the player owns.
    std::vector<HexTile::REF> possibles_hex_moves = hexes.get_player_hexes(get_current_player_id());

    // If the "from" hex has value, remove the hexes that are not reachable from the "from" hex.
    if (from.has_value())
    {
        std::erase_if(possibles_hex_moves, [this, &from](const HexTile::REF& hex_ref)
        {
            return !path_exist_between(from.value().get(), hex_ref.get(), get_current_player_id());
        });
    }
    // Else, we remove the hexes that are not reachable from at least one building own by the player
    else
    {
        std::vector<HexTile::REF> buildings;
        std::ranges::copy_if(possibles_hex_moves, std::back_inserter(buildings), [](const HexTile::REF& hex_ref) { return hex_ref.get().has_building(); });
        std::erase_if(possibles_hex_moves, [this, &buildings](const HexTile::REF& hex_ref)
        {
            return !std::ranges::any_of(buildings, [this, &hex_ref](const HexTile::REF& building_ref)
            {
                return path_exist_between(building_ref.get(), hex_ref.get(), get_current_player_id());
            });
        });
    }

    // For every possible hex move, get the neighbors that are not already in possibles_hex_moves and check if they are valid for a move.
    std::vector<HexTile::REF> hex_to_add{};
    for (HexTile::REF& possible_hex_move_ref : possibles_hex_moves)
    {
        std::vector<HexTile::REF> neighbors = hexes.get_neighbors_if(possible_hex_move_ref.get(), [&possibles_hex_moves, moving_entity, this](HexTile& neighbor)
        {
            // Neighbor is valid if it is not already in possibles_hex_moves
            if (engine_utils::contains(possibles_hex_moves, [&neighbor](const HexTile::REF& hex_ref) { return hex_ref.get() == neighbor; }))
                return false;

            // Neighbor is valid if it is a territory
            if (neighbor.get_type() != HexType::Territory)
                return false;

            if (moving_entity->get_decoration() == HexEntity::Hero)
                return true;

            // Neighbor is valid if it has an entity not own by the player and the entity is not stronger than the entity that is moving
            if (neighbor.has_entity() && neighbor.get_player() != get_current_player_id() && moving_entity->get_level() <= neighbor.get_entity()->get_level())
                return false;

            // Neighbor is valid if the safe level of the neighbor is not stronger than the entity that is moving
            if (moving_entity->get_level() <= neighbor.safe_level)
                return false;

            return true;
        });

        hex_to_add.insert(hex_to_add.end(), neighbors.begin(), neighbors.end());
    }
    possibles_hex_moves.insert(possibles_hex_moves.end(), hex_to_add.begin(), hex_to_add.end());

    // Remove the hexes with buildings that the player own, the hexes with units that the player own except same level units (for merge) and bandits
    // and if the moving_entity is a building, remove the hexes that the player do not own.
    std::erase_if(possibles_hex_moves, [this, &moving_entity, &from](const HexTile::REF& hex_ref)
    {
        const HexTile& hex = hex_ref.get();
        return
            (from.has_value() && from == hex) ? false :
            (hex.has_building() && hex.get_player() == get_current_player_id()) ||
            (hex.has_entity() && !hex.has_building() && hex.get_decoration() != HexEntity::Bandit && hex.get_player() == get_current_player_id() && !is_merge_possible(moving_entity, hex)) ||
            (moving_entity->is_building() && hex.get_player() != get_current_player_id());
    });

    return possibles_hex_moves;
}

bool GameManager::is_merge_possible(const Entity::SP& moving_entity, const HexTile& hex)
{
    return hex.get_entity()->get_level() == moving_entity->get_level() && moving_entity->get_level() < constants::hero_level;
}

Player& GameManager::get_player_by_id(int id)
{
    for (Player& player : m_players)
        if (player.id == id) 
            return player;
    logs::error("Error: No player with id {} found", id);
    throw std::runtime_error("Error: No player with this id found");
}

void GameManager::save_action_to_stack(const HexTile& to, const Entity::SP& moving_entity, const std::optional<HexTile>& from) {
    const int previous_owner = to.get_player();

    const Action action {
        .from = from,
        .to = to,
        .moving_entity = moving_entity,
        .previous_entity = to.get_entity(),
        .previous_player_to = previous_owner,
        .cost = from.has_value() ? 0 : moving_entity->get_price(),
        .previous_hex_tiles_states = m_modified_tiles
    };
    m_actions.push(action);
    m_modified_tiles.clear();
}

void GameManager::undo_last_action()
{
    if (m_actions.empty())
        return;

    HexContainer& hexes = m_map->get_map();
    const Action& action = m_actions.top();

    if (action.from.has_value())
    {
        // It is a unit movement
        hexes.at(action.from.value().get_position()) = action.from.value();
        hexes.at(action.to.get_position()) = action.to;

        std::dynamic_pointer_cast<Unit>(action.moving_entity)->has_moved_in_turn = false;
        std::dynamic_pointer_cast<Unit>(action.moving_entity)->bouncing = true;
    }
    else
    {
        // It is an entity placement
        hexes.at(action.to.get_position()) = action.to;

        player_playing().money += action.cost;
    }

    for (const HexTile& hex : action.previous_hex_tiles_states)
        hexes.at(hex.get_position()) = hex;

    m_actions.pop();

    if (get_current_player_id() != action.previous_player_to && !check_player_dead(action.previous_player_to))
    {
        get_player_by_id(action.previous_player_to).dead = false;
        m_ranking.pop_back();
    }

    insert_territories_linked_to_castle(player_playing());
    if (action.previous_player_to != 0 && get_current_player_id() != action.previous_player_to)
        insert_territories_linked_to_castle(get_player_by_id(action.previous_player_to));
    compute_safe_level_and_fences();
    player_playing().money_per_turn = compute_player_earn();
    update_player_ui();
}

void GameManager::move_decoration(HexTile& from, HexTile& to)
{
    if (from == to) 
        return;
    apply_move_logic(from.get_entity(), to, from);
    update_player_ui();
}

void GameManager::place_unit(HexTile& to, const HexEntity& entity_type)
{
    Entity::SP entity = nullptr;
    switch (entity_type)
    {
        case HexEntity::Villager:
            entity = std::make_shared<Villager>();
            break;
        case HexEntity::Soldier:
            entity = std::make_shared<Soldier>();
            break;
        case HexEntity::Knight:
            entity = std::make_shared<Knight>();
            break;
        case HexEntity::Tower:
            entity = std::make_shared<Tower>();
            break;
    }

    apply_move_logic(entity, to);
    player_playing().money -= entity->get_price();
    update_player_ui();
}

Entity::SP GameManager::check_and_apply_merge(const Entity::SP& entity, const HexTile &to) const
{
    Entity::SP merged_entity = nullptr;
    if (to.has_entity() && !to.has_building() && !entity->is_building()
        && to.get_player() == get_current_player_id() && to.get_entity()->get_level() == entity->get_level())
    {
        if (entity->get_level() == constants::villager_level)
            merged_entity = std::make_shared<Soldier>();
        if (entity->get_level() == constants::soldier_level)
            merged_entity = std::make_shared<Knight>();
        if (entity->get_level() == constants::knight_level)
            merged_entity = std::make_shared<Hero>();
    }

    return merged_entity ? merged_entity : entity;
}

void GameManager::check_cut_territory(const int previous_owner)
{
    if (previous_owner == 0)
        return;

    HexContainer& hexes = m_map->get_map();
    const std::vector<HexTile::REF> hexes_of_previous_player_with_castle = hexes.get_player_castles(previous_owner);
    std::vector<HexTile::REF> hexes_to_remove;
    for (const HexTile::REF& hex_ref : get_player_by_id(previous_owner).territories)
    {
        bool has_path_to_castle = false;
        for (const HexTile::REF& castle_ref : hexes_of_previous_player_with_castle)
        {
            if (path_exist_between(hex_ref, castle_ref, previous_owner))
            {
                has_path_to_castle = true;
                break;
            }
        }
        if (!has_path_to_castle)
        {
            m_modified_tiles.push_back(hex_ref.get());
            if (hex_ref.get().has_entity() && !hex_ref.get().has_building())
                hex_ref.get().set_entity(std::make_shared<Bandit>());
            else
                hex_ref.get().set_entity(nullptr);
            hex_ref.get().set_player(0);
            hexes_to_remove.push_back(hex_ref);
        }
    }
    for (const HexTile::REF& hex_ref : hexes_to_remove)
        get_player_by_id(previous_owner).territories.erase(hex_ref);
}

bool GameManager::check_player_dead(int player_id) const
{
    const HexContainer& hexes = m_map->get_map();
    return hexes.count_if([player_id](const HexTile& hex) { return hex.get_player() == player_id && hex.get_decoration() == HexEntity::Castle; }) == 0;
}

void GameManager::apply_move_logic(const Entity::SP& entity, HexTile& to, const std::optional<HexTile::REF> from)
{
    const HexTile previous_to = to;
    const std::optional<HexTile> previous_from = from;

    const Unit::SP unit = std::dynamic_pointer_cast<Unit>(entity);
    if (unit && to.get_player() != get_current_player_id())
        unit->has_moved_in_turn = true;

    const Entity::SP final_entity = check_and_apply_merge(entity, to);
    const int previous_owner = to.get_player();
    const HexEntity previous_entity = to.get_decoration();

    to.set_player(get_current_player_id());
    to.set_entity(final_entity);

    player_playing().territories.insert(std::ref(to));
    if (previous_owner != 0 && previous_owner != get_current_player_id())
        get_player_by_id(previous_owner).territories.erase(to);

    if (from.has_value())
        from.value().get().set_entity(nullptr);

    if (previous_entity == HexEntity::Castle && check_player_dead(previous_owner))
    {
        get_player_by_id(previous_owner).dead = true;
        m_ranking.emplace_back(get_player_by_id(previous_owner));
        if (m_popup_ui)
            m_popup_ui->show_popup(PopupFactory::create_player_eliminated(get_player_by_id(previous_owner)));
    }

    check_cut_territory(previous_owner);

    insert_territories_linked_to_castle(player_playing());

    save_action_to_stack(previous_to, entity, previous_from);

    compute_safe_level_and_fences();
    player_playing().money_per_turn = compute_player_earn();

    const int players_alive = static_cast<int>(std::ranges::count_if(m_players, [](const Player& player){ return !player.dead; }));
    if (players_alive <= 1)
    {
        m_ranking.emplace_back(player_playing());
        if (m_endgame_ui)
            m_endgame_ui->set_ranking(m_ranking);
    }
}

bool GameManager::can_move_decoration(const HexTile& hex) const
{
    return hex.has_movable_decoration() && hex.get_player() == get_current_player_id();
}

bool GameManager::path_exist_between(const HexTile& from, const HexTile& to, int player) const
{
    if (from == to)
        return true;

    HexContainer& hexes = m_map->get_map();
    std::unordered_map<HexTile, HexTile, HexTile::Hash> came_from;
    std::unordered_map<HexTile, int, HexTile::Hash> cost_so_far;
    std::priority_queue<QueueItem> frontier;
    frontier.emplace(from, 0);
    came_from[from] = from;
    cost_so_far[from] = 0;

    while (!frontier.empty())
    {
        HexTile current = frontier.top().tile;
        frontier.pop();
        if (current == to)
            return true;

        const std::vector<HexTile::REF> neighbors = hexes.get_neighbors_if(current, [this, player](const HexTile& hex) { return hex.get_player() == player; });
        for (const HexTile::REF& next_ref : neighbors)
        {
            HexTile& next = next_ref.get();
            const int new_cost = cost_so_far[current] + 1;
            if (!cost_so_far.contains(next) || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                frontier.emplace(next, new_cost + HexTile::distance(next, to));
                came_from[next] = current;
            }
        }
    }

    return false;
}

void GameManager::compute_safe_level_and_fences() const
{
    reset_hexes_safety();
    compute_entities_safety();
    compute_fences();
}

void GameManager::reset_hexes_safety() const
{
    for (HexTile& hex : m_map->get_map() | std::views::values)
    {
        if (hex.has_building())
        {
            hex.safe = true;
            hex.safe_level = hex.get_entity()->get_level();
        }
        else
        {
            hex.safe = false;
            hex.safe_level = 0;
        }
        hex.remove_fences();
    }
}

void GameManager::compute_entities_safety() const
{
    HexContainer& hexes = m_map->get_map();
    const std::vector<HexTile::REF> hexes_with_entity = hexes.get_hexes_if([](const HexTile& hex) { return hex.has_entity(); });
    // For every hexes that has an entity, check the neighbors of the entity and set them as "safe" (if the entity is a building) and set the safe level if they are owned by the same player.
    for (const HexTile::REF& hex_with_entity_ref : hexes_with_entity)
    {
        std::vector<HexTile::REF> neighbors_of_same_player = hexes.get_neighbors_if(hex_with_entity_ref.get(), [&hex_with_entity_ref](const HexTile& neighbor)
        {
            return neighbor.get_player() == hex_with_entity_ref.get().get_player();
        });
        for (const HexTile::REF& neighbor_ref : neighbors_of_same_player)
        {
            if (hex_with_entity_ref.get().has_building()) 
                neighbor_ref.get().safe = true;
            neighbor_ref.get().safe_level = std::max(neighbor_ref.get().safe_level, hex_with_entity_ref.get().get_entity()->get_level());
        }
    }
}

void GameManager::compute_fences() const
{
    HexContainer& hexes = m_map->get_map();
    // For every hex that are tagged "safe", check for every direction if the neighbor is safe or not. If it's the case then, we don't have to put a fence.
    const std::vector<HexTile::REF> hexes_safe = hexes.get_hexes_if([](const HexTile& hex) { return hex.safe; });
    for (const HexTile::REF& hex_ref : hexes_safe)
    {
        HexTile& hex = hex_ref.get();
        for (const HexDirection direction : AllHexDirections)
        {
            std::optional<HexTile::REF> neighbor_ref = hexes.get_neighbor(hex, direction);
            const bool need_fence = !neighbor_ref.has_value() || !neighbor_ref.value().get().safe || neighbor_ref.value().get().get_player() != hex.get_player();
            hex.set_fence(direction, need_fence);
        }
    }
}

void GameManager::insert_territories_linked_to_castle(Player &player) const
{
    player.territories.clear();
    HexContainer& hexes = m_map->get_map();
    const std::vector<HexTile::REF> castles_of_player = hexes.get_player_castles(player.id);
    for (const HexTile::REF& hex_ref : hexes.get_player_hexes(player.id))
    {
        bool has_path_to_castle = false;
        for (const HexTile::REF& castle_ref : castles_of_player)
        {
            if (path_exist_between(hex_ref, castle_ref, player.id))
            {
                has_path_to_castle = true;
                break;
            }
        }
        if (has_path_to_castle) 
            player.territories.insert(hex_ref);
    }
}

void GameManager::init_players_active_territories()
{
    for (Player& player : m_players)
        insert_territories_linked_to_castle(player);
}

void GameManager::start_game()
{
    setup_players();
    m_round_number = 1;
    if (std::ranges::count_if(m_players, [](const Player& player){ return !player.dead; }) > 0 && m_end_turn_callback)
        m_end_turn_callback();
}

void GameManager::update_player_ui()
{
    std::vector<HexEntity> not_buyable_entities;

    if (player_playing().money < constants::knight_price)
        not_buyable_entities.push_back(HexEntity::Knight);
    if (player_playing().money < constants::soldier_price)
        not_buyable_entities.push_back(HexEntity::Soldier);
    if (player_playing().money < constants::tower_price)
        not_buyable_entities.push_back(HexEntity::Tower);
    if (player_playing().money < constants::villager_price)
        not_buyable_entities.push_back(HexEntity::Villager);

    m_player_ui->set_player_info(player_playing(), not_buyable_entities, !m_actions.empty());
}

void GameManager::set_player_ui(PlayerInfoWidget::SP ui)
{
    m_player_ui = std::move(ui);
    m_player_ui->set_end_turn_callback([this] { end_turn(); });
    m_player_ui->add_undo_callback([this] { undo_last_action(); });
}

void GameManager::check_if_player_can_afford_units_salary()
{
    HexContainer& hexes = m_map->get_map();
    for (Player& player: m_players)
    {
        if (player.dead)
            continue;

        player.money_per_turn = compute_player_earn();
        if (player.money_per_turn < 0 && std::abs(player.money_per_turn) > player.money)
        {
            player.money = 0;
            for (HexTile::REF& hex_ref : hexes.get_hexes_if([player](const HexTile::REF hex){ return hex.get().get_player() == player.id && hex.get().has_entity() && !hex.get().has_building(); }))
                hex_ref.get().set_entity(std::make_shared<Bandit>());
        }
    }
    compute_safe_level_and_fences();
}

void GameManager::reset_units_state_of_current_player() const
{
    HexContainer& hexes = m_map->get_map();
    // Reset the has_moved_in_turn for all units owned by the current player
    for (const HexTile::REF& hex_ref : hexes.get_player_hexes(get_current_player_id()))
        if (const Unit::SP unit = std::dynamic_pointer_cast<Unit>(hex_ref.get().get_entity()))
            unit->has_moved_in_turn = false;
}

void GameManager::move_bandit_if_new_round()
{
    m_number_of_turn++;
    if (m_number_of_turn % m_players.size() != 0)
        return;

    m_round_number++;
    m_number_of_turn = 0;
    HexContainer& hexes = m_map->get_map();
    for (HexTile::REF& hex_ref : hexes.get_decoration_hexes(HexEntity::Bandit))
    {
        std::vector<HexTile::REF> neighbors = hexes.get_neighbors_if(hex_ref, [](const HexTile::REF& hex)
        {
            return hex.get().get_type() == HexType::Territory && !hex.get().has_entity() && hex.get().safe_level == constants::bandit_level;
        });
        if (neighbors.empty())
            continue;
        HexTile::REF& to = neighbors[engine_random::next(0, static_cast<int>(neighbors.size() - 1))];
        to.get().set_entity(hex_ref.get().get_entity());
        hex_ref.get().set_entity(nullptr);
    }
}

void GameManager::end_turn()
{
    move_bandit_if_new_round();
    check_if_player_can_afford_units_salary();
    reset_units_state_of_current_player();

    do
        m_index_player_playing = (m_index_player_playing + 1) % static_cast<int>(m_players.size());
    while (player_playing().dead);

    m_actions = {};

    player_playing().money_per_turn = compute_player_earn();
    player_playing().money = std::max(0, player_playing().money + player_playing().money_per_turn);
    update_player_ui();

    if (m_end_turn_callback)
        m_end_turn_callback();
}

int GameManager::compute_player_earn() const
{
    // Check all hexes own by current player if there is an entity (cost per turn) or a bandit (no earn from this hex) in order to get total earn
    std::unordered_set<HexTile::REF, Player::Hash> player_territories = player_playing().territories;
    std::erase_if(player_territories, [](const HexTile::REF& hex_ref){ return hex_ref.get().has_entity() && hex_ref.get().get_decoration() == HexEntity::Bandit; });
    int earn = static_cast<int>(player_territories.size());
    for (const HexTile::REF& hex_ref : player_territories)
        if (hex_ref.get().has_entity())
            earn -= hex_ref.get().get_entity()->get_cost_per_turn();

    return earn;
}

void GameManager::setup_players()
{
    m_players = {
           Player{1, "Player 1", constants::player_colors[0]},
           Player{2, "Player 2", constants::player_colors[1]},
           Player{3, "Player 3", constants::player_colors[2]},
           Player{4, "Player 4", constants::player_colors[3]},
    };

    m_popup_ui->clear();
    m_player_ui->show();

    const std::set<int> players_id = compute_number_of_player();

    for (Player& player : m_players)
        if (!players_id.contains(player.id))
            player.dead = true;

    if (players_id.size() > 4)
    {
        logs::error("Too many players, maximum is 4");
        m_popup_ui->show_popup(PopupFactory::create_load_map_error("Too many players, maximum is 4"));
        m_player_ui->hide();
        return;
    }
    if (players_id.size() < 2)
    {
        logs::error("Not enough players, minimum is 2");
        m_popup_ui->show_popup(PopupFactory::create_load_map_error("Not enough players, minimum is 2"));
        m_player_ui->hide();
        return;
    }

    init_players_active_territories();
    m_index_player_playing = *players_id.begin() - 1;
    player_playing().money_per_turn = compute_player_earn();
    player_playing().money = std::max(0, player_playing().money + player_playing().money_per_turn);
    update_player_ui();
}

std::set<int> GameManager::compute_number_of_player() const
{
    HexContainer& hexes = m_map->get_map();

    std::set<int> players_id;
    for (const HexTile::REF& city_hall_ref : hexes.get_castles())
    {
        const int player_id = city_hall_ref.get().get_player();
        if (player_id > 0)
            players_id.insert(player_id);
    }
    return players_id;
}