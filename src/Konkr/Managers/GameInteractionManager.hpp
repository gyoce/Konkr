#ifndef KONKR_GAME_INTERACTION_MANAGER_HPP
#define KONKR_GAME_INTERACTION_MANAGER_HPP

#include "Engine/Scenes/SceneObject.hpp"
#include "Engine/Graphics/Sprite.hpp"

#include "Konkr/Hex/Map.hpp"
#include "Konkr/Managers/GameManager.hpp"

class GameInteractionManager final : public SceneObject
{
public:
    GameInteractionManager(Map::SP map, GameManager::SP game_manager);

    void on_mouse_button_down(const Event::MouseButton& event) override;
    void on_mouse_button_up(const Event::MouseButton& event) override;
    void on_mouse_move(const Event::MouseMove& event) override;
    void draw() override;
    void update() override;

    void set_player_ui(PlayerInfoWidget::SP player_ui);

    using SP = std::shared_ptr<GameInteractionManager>;

private:
    void on_left_mouse_button_down(const Event::MouseButton& event);
    void on_left_mouse_button_up(const Event::MouseButton& event);
    void on_right_mouse_button_up(const Event::MouseButton&);

    void end_turn_callback();

    /// <summary>
    /// Is the callback method called when the user left-click on a unit button on the UI.
    /// </summary>
    void handle_unit_selection(HexEntity entity_type);

    void handle_undo() const;

    static SpriteType get_tower_sprite_type_for_player(int player_id);

    Map::SP m_map;
    GameManager::SP m_game_manager;
    PlayerInfoWidget::SP m_player_ui;
    Sprite::SP m_decoration_moving_sprite = nullptr;
    std::optional<HexTile::REF> m_from_hex = std::nullopt;
    std::optional<HexTile::REF> m_to_hex = std::nullopt;
    std::vector<HexTile::REF> m_possible_hex_moves;
    bool dragging = false;
    HexEntity m_selected_entity_type = HexEntity::None;
    std::vector<Entity::SP> m_player_units;
};

#endif // KONKR_GAME_INTERACTION_MANAGER_HPP
