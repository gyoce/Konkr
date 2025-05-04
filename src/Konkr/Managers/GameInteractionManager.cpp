#include "Konkr/Managers/GameInteractionManager.hpp"

#include "Engine/Graphics/Cursor.hpp"
#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Managers/TimeManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Engine/Utils/Utils.hpp"
#include "Konkr/Models/Buildings/Tower.hpp"
#include "Konkr/Models/Units/Knight.hpp"
#include "Konkr/Models/Units/Soldier.hpp"
#include "Konkr/Models/Units/Villager.hpp"

GameInteractionManager::GameInteractionManager(Map::SP map, GameManager::SP game_manager)
    : m_map(std::move(map)), m_game_manager(std::move(game_manager))
{
    m_game_manager->set_end_turn_callback([this] { end_turn_callback(); });
}

void GameInteractionManager::set_player_ui(PlayerInfoWidget::SP player_ui)
{
    m_player_ui = std::move(player_ui);
    m_player_ui->set_on_unit_selected_callback([this](const HexEntity unit_type) { handle_unit_selection(unit_type); });
    m_player_ui->add_undo_callback([this] { handle_undo(); });
}

void GameInteractionManager::on_mouse_button_down(const Event::MouseButton& event)
{
    if (event.button == Mouse::Left)
        on_left_mouse_button_down(event);
}

void GameInteractionManager::on_mouse_button_up(const Event::MouseButton& event)
{
    if (event.button == Mouse::Left)
        on_left_mouse_button_up(event);
    else if (event.button == Mouse::Right)
        on_right_mouse_button_up(event);
}

void GameInteractionManager::on_mouse_move(const Event::MouseMove& event)
{
    if (dragging && m_decoration_moving_sprite)
        m_decoration_moving_sprite->set_position(event.position.cast<float>() - m_decoration_moving_sprite->get_size() / 2.0f);
    else
    {
        const std::optional<HexTile::REF> hex = m_map->get_hex_by_screen_coords(event.position);
        if (hex.has_value() && hex.value().get().has_movable_decoration())
            Cursor::set_active_cursor(Cursor::Type::Clickable);
    }
}

void GameInteractionManager::draw()
{
    if (m_decoration_moving_sprite)
        m_decoration_moving_sprite->draw();
}

void GameInteractionManager::update()
{
    for (const Entity::SP& unit : m_player_units)
    {
        if (unit->bouncing)
        {
            unit->bounce_accumulator += TimeManager::get_delta_time();
            unit->bounce_offset = std::abs(std::sin(unit->bounce_accumulator * constants::bounce_speed) * constants::bounce_amplitude);
        }
    }
}

void GameInteractionManager::on_left_mouse_button_down(const Event::MouseButton& event)
{
    // If the selected entity type is not unknown, it means that the user has selected a unit from the UI to place on the map.
    if (m_selected_entity_type != HexEntity::None)
    {
        m_to_hex = m_map->get_hex_by_screen_coords(event.position);
        if (!m_to_hex.has_value() || !engine_utils::contains(m_possible_hex_moves, [this](const HexTile::REF& hex_ref) { return m_to_hex.value().get() == hex_ref.get(); }))
            return;
        m_game_manager->place_unit(m_to_hex.value().get(), m_selected_entity_type);

        // If the user place a unit, and he places it without change the "has_moved_in_turn" tag, we need to update the bouncing state
        if (const Unit::SP unit = std::dynamic_pointer_cast<Unit>(m_to_hex.value().get().get_entity()))
        {
            unit->bouncing = !unit->has_moved_in_turn;
            m_player_units.push_back(unit);
        }
        m_selected_entity_type = HexEntity::None;
        m_decoration_moving_sprite = nullptr;
        for (HexTile::REF& hex_ref : m_possible_hex_moves)
            hex_ref.get().highlighted = false;
        return;
    }

    m_from_hex = m_map->get_hex_by_screen_coords(event.position);
    if (!m_from_hex.has_value() || !m_game_manager->can_move_decoration(m_from_hex.value().get()))
        return;

    // Here m_from_hex is a hex that has a movable decoration
    dragging = true;
    HexTile& from_hex = m_from_hex.value().get();
    m_decoration_moving_sprite = std::make_shared<Sprite>(from_hex.get_sprite_decoration());
    m_decoration_moving_sprite->set_size(m_map->get_decoration_size(from_hex.get_sprite_decoration(), from_hex.get_sprite_type_decoration()));
    m_decoration_moving_sprite->set_position(event.position.cast<float>() - m_decoration_moving_sprite->get_size() / 2.0f);
    from_hex.disable_decoration = true;

    m_possible_hex_moves = m_game_manager->get_possible_hex_moves(from_hex.get_entity(), m_from_hex);
    for (HexTile::REF& hex_ref : m_possible_hex_moves)
        hex_ref.get().highlighted = true;
}

void GameInteractionManager::on_left_mouse_button_up(const Event::MouseButton& event)
{
    if (m_selected_entity_type != HexEntity::None)
        return;

    dragging = false;
    if (m_decoration_moving_sprite == nullptr)
        return;

    // We can move an entity from one hex to another if the "to" hex is in the list of possible hex moves
    m_to_hex = m_map->get_hex_by_screen_coords(event.position);
    if (m_to_hex.has_value() && engine_utils::contains(m_possible_hex_moves, [this](const HexTile::REF& hex_ref) { return m_to_hex.value().get() == hex_ref.get(); }))
    {
        Entity::SP entity = m_from_hex.value().get().get_entity();
        m_game_manager->move_decoration(m_from_hex.value().get(), m_to_hex.value().get());
        std::erase_if(m_player_units, [entity](const Entity::SP& e) { return e == entity; });

        if (const Unit::SP unit = std::dynamic_pointer_cast<Unit>(m_to_hex.value().get().get_entity()))
        {
            unit->bouncing = !unit->has_moved_in_turn;
            m_player_units.push_back(unit);
        }
    }

    m_from_hex.value().get().disable_decoration = false;
    m_decoration_moving_sprite = nullptr;
    for (HexTile::REF& hex_ref : m_possible_hex_moves)
        hex_ref.get().highlighted = false;
}

void GameInteractionManager::on_right_mouse_button_up(const Event::MouseButton&)
{
    // If the user wanted to place a new entity, and he right-clicks, it means that he wants to cancel the action.
    if (m_selected_entity_type != HexEntity::None)
    {
        m_selected_entity_type = HexEntity::None;
        m_decoration_moving_sprite = nullptr;
        for (HexTile::REF& hex_ref : m_possible_hex_moves)
            hex_ref.get().highlighted = false;
    }
}

void GameInteractionManager::end_turn_callback()
{
    HexContainer& hexes = m_map->get_map();

    for (const Entity::SP& unit : m_player_units)
    {
        unit->bouncing = false;
        unit->bounce_accumulator = 0.0f;
    }
    
    m_player_units = hexes.get_player_units_entities(m_game_manager->get_current_player_id());
    for (const Entity::SP& unit : m_player_units)
        unit->bouncing = true;
}

void GameInteractionManager::handle_unit_selection(const HexEntity entity_type)
{
    if (entity_type == HexEntity::None)
        return;

    m_selected_entity_type = entity_type;
    Entity::SP temp_entity = nullptr;

    dragging = true;

    SpriteType sprite_type = SpriteType::None;
    switch (m_selected_entity_type)
    {
    case HexEntity::Villager:
        sprite_type = SpriteType::Villager;
        temp_entity = std::make_shared<Villager>();
        break;
    case HexEntity::Soldier:
        sprite_type = SpriteType::Soldier;
        temp_entity = std::make_shared<Soldier>();
        break;
    case HexEntity::Knight:
        sprite_type = SpriteType::Knight;
        temp_entity = std::make_shared<Knight>();
        break;
    case HexEntity::Tower:
        sprite_type = get_tower_sprite_type_for_player(m_game_manager->get_current_player_id());
        temp_entity = std::make_shared<Tower>();
        break;
    }

    m_decoration_moving_sprite = std::make_shared<Sprite>(ResourceManager::get_sprite(sprite_names::from_sprite_type(sprite_type)));
    m_decoration_moving_sprite->set_size(m_map->get_decoration_size(ResourceManager::get_sprite(sprite_names::from_sprite_type(sprite_type)), sprite_type));
    m_decoration_moving_sprite->set_position(Mouse::get_position().cast<float>() - m_decoration_moving_sprite->get_size() / 2.0f);

    for (HexTile::REF& hex_ref : m_possible_hex_moves)
        hex_ref.get().highlighted = false;

    m_possible_hex_moves = m_game_manager->get_possible_hex_moves(temp_entity, std::nullopt);
    for (HexTile::REF& hex_ref : m_possible_hex_moves)
        hex_ref.get().highlighted = true;
}

void GameInteractionManager::handle_undo() const
{
    for (HexTile& hex : m_map->get_map() | std::views::values)
    {
	hex.disable_decoration = false;
        hex.highlighted = false;
    }
}

SpriteType GameInteractionManager::get_tower_sprite_type_for_player(int player_id)
{
    switch (player_id)
    {
    case 1:
        return SpriteType::Tower1;
    case 2:
        return SpriteType::Tower2;
    case 3:
        return SpriteType::Tower3;
    case 4:
        return SpriteType::Tower4;
    default:
        logs::error("GameInteractionManager::get_tower_sprite_type_for_player: Invalid player id: {}", player_id);
        return SpriteType::None;
    }
}
