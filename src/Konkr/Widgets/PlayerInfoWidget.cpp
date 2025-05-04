#include "Konkr/Widgets/PlayerInfoWidget.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Konkr/Utils/Constants.hpp"

PlayerInfoWidget::PlayerInfoWidget()
{
    GuiPanel::set_background_color(m_background_color);

    const GuiHorizontalLayout::SP main_layout = std::make_shared<GuiHorizontalLayout>();
    main_layout->set_stretch({ 1.0f, 1.0f });
    GuiPanel::set_layout(main_layout);

    // 1st panel : Undo button
    const GuiAnchorLayout::SP undo_layout = std::make_shared<GuiAnchorLayout>();
    undo_layout->set_stretch({ 0.1f, 1.0f });
    main_layout->add_layout(undo_layout);

    m_undo_button = std::make_shared<GuiButton>();
    m_undo_button->set_stretch({ 0.9f, 0.75f });
    m_undo_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    m_undo_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    m_undo_button->set_text("Undo");
    m_undo_button->set_key_binding(Keyboard::Key::U);
    m_undo_button->set_on_click_callback([this] { send_undo_callback(); });
    undo_layout->add_widget(m_undo_button, Horizontal::Center, Vertical::Center);

    // 2nd panel : Player information
    const GuiVerticalLayout::SP player_info_layout = std::make_shared<GuiVerticalLayout>();
    player_info_layout->set_stretch({ 0.25f, 1.0f });
    main_layout->add_layout(player_info_layout);

    const GuiAnchorLayout::SP name_layout = std::make_shared<GuiAnchorLayout>();
    name_layout->set_stretch({ 1.0f, 0.5f });
    player_info_layout->add_layout(name_layout);

    m_name_label = std::make_shared<GuiText>();
    m_name_label->set_text("Player");
    m_name_label->set_stretch({ 0.5f, 1.0f });
    name_layout->add_widget(m_name_label, Horizontal::Center, Vertical::Center);

    const GuiHorizontalLayout::SP money_layout = std::make_shared<GuiHorizontalLayout>();
    money_layout->set_stretch({ 0.9f, 0.5f });
    money_layout->set_padding_between_items({ 10, 0 });
    player_info_layout->add_layout(money_layout);

    // 1st sub-panel : total money
    const GuiHorizontalLayout::SP total_money_layout = std::make_shared<GuiHorizontalLayout>();
    total_money_layout->set_stretch({ 0.5f, 1.0f });

    const GuiImage::SP total_money_img = std::make_shared<GuiImage>();
    total_money_img->set_image(ResourceManager::get_sprite(sprite_names::ui_money_idle));
    total_money_img->set_stretch({ 0.2f, 0.75f });
    total_money_layout->add_widget(total_money_img);

    m_total_money_label = std::make_shared<GuiText>();
    m_total_money_label->set_text("100");
    m_total_money_label->set_stretch({ 0.8f, 1.0f });
    total_money_layout->add_widget(m_total_money_label);
    money_layout->add_layout(total_money_layout);

    // 2nd sub-panel : earned money
    const GuiHorizontalLayout::SP earned_money_layout = std::make_shared<GuiHorizontalLayout>();
    earned_money_layout->set_stretch({ 0.5f, 1.0f });

    m_earned_money_img = std::make_shared<GuiImage>();
    m_earned_money_img->set_image(ResourceManager::get_sprite(sprite_names::ui_money_incoming));
    m_earned_money_img->set_stretch({ 0.2f, 0.75f });
    earned_money_layout->add_widget(m_earned_money_img);

    m_earned_money_label = std::make_shared<GuiText>();
    m_earned_money_label->set_text("2");
    m_earned_money_label->set_stretch({ 0.8f, 1.0f });
    earned_money_layout->add_widget(m_earned_money_label);
    money_layout->add_layout(earned_money_layout);

    // 3rd panel : Unit picking
    const GuiHorizontalLayout::SP unit_layout = std::make_shared<GuiHorizontalLayout>();
    unit_layout->set_stretch({ 0.55f, 1.0f });
    unit_layout->set_padding_between_items({ 10, 0 });
    main_layout->add_layout(unit_layout);

    m_villager_button = std::make_shared<GuiButton>();
    m_villager_button->set_stretch({ 0.075f, 0.8f });
    m_villager_button->set_background_texture(ResourceManager::get_sprite(sprite_names::villager));
    m_villager_button->set_on_click_callback([this] { select_unit_type(HexEntity::Villager); });
    m_villager_button->set_key_binding(Keyboard::Key::Num1);
    unit_layout->add_widget(m_villager_button);

    m_soldier_button = std::make_shared<GuiButton>();
    m_soldier_button->set_stretch({ 0.075f, 0.8f });
    m_soldier_button->set_background_texture(ResourceManager::get_sprite(sprite_names::soldier));
    m_soldier_button->set_on_click_callback([this] { select_unit_type(HexEntity::Soldier); });
    m_soldier_button->set_key_binding(Keyboard::Key::Num2);
    unit_layout->add_widget(m_soldier_button);

    m_knight_button = std::make_shared<GuiButton>();
    m_knight_button->set_stretch({ 0.075f, 0.8f });
    m_knight_button->set_background_texture(ResourceManager::get_sprite(sprite_names::knight));
    m_knight_button->set_on_click_callback([this] { select_unit_type(HexEntity::Knight); });
    m_knight_button->set_key_binding(Keyboard::Key::Num3);
    unit_layout->add_widget(m_knight_button);

    m_tower_button = std::make_shared<GuiButton>();
    m_tower_button->set_stretch({ 0.05f, 0.8f });
    m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower1));
    m_tower_button->set_on_click_callback([this] { select_unit_type(HexEntity::Tower); });
    m_tower_button->set_key_binding(Keyboard::Key::Num4);
    unit_layout->add_widget(m_tower_button);

    // 4th panel : End turn button
    const GuiAnchorLayout::SP end_turn_layout = std::make_shared<GuiAnchorLayout>();
    end_turn_layout->set_stretch({ 0.1f, 1.0f });
    main_layout->add_layout(end_turn_layout);

    const GuiButton::SP end_turn_button = std::make_shared<GuiButton>();
    end_turn_button->set_stretch({ 0.9f, 0.75f });
    end_turn_button->set_background_texture(ResourceManager::get_sprite(sprite_names::ui_blue_button));
    end_turn_button->set_background_texture_hovered(ResourceManager::get_sprite(sprite_names::ui_blue_button_hovered));
    end_turn_button->set_text("End");
    end_turn_button->set_key_binding(Keyboard::Key::E);
    end_turn_button->set_on_click_callback([this] { send_end_turn_callback(); });
    end_turn_layout->add_widget(end_turn_button, Horizontal::Center, Vertical::Center);
}

void PlayerInfoWidget::set_player_info(const Player& player, const std::vector<HexEntity>& not_buyable_entities, bool undo_active)
{
    m_background_color = player.color;
    m_background_color.a = 128;

    m_name_label->set_text(player.name, true);
    m_total_money_label->set_text(std::to_string(player.money), true);
    m_earned_money_label->set_text(std::to_string(player.money_per_turn), true);
    if (player.money_per_turn < 0)
    {
        m_earned_money_img->set_image(ResourceManager::get_sprite(sprite_names::ui_money_outgoing));
        m_earned_money_label->set_text_color(Color::Red);
    }
    else
    {
        m_earned_money_img->set_image(ResourceManager::get_sprite(sprite_names::ui_money_incoming));
        m_earned_money_label->set_text_color(Color::Green);
    }

    m_undo_button->set_disable(!undo_active);

    reset_unit_buttons(player);
    update_buyable_entities_button(player, not_buyable_entities);
}

void PlayerInfoWidget::select_unit_type(const HexEntity type) const
{
    if (m_on_unit_selected_callback)
        m_on_unit_selected_callback(type);
}

void PlayerInfoWidget::send_end_turn_callback() const
{
    if (m_end_turn_callback)
        m_end_turn_callback();
}

void PlayerInfoWidget::send_undo_callback() const
{
    for (const std::function<void()>& callback : m_undo_callbacks)
        callback();
}

void PlayerInfoWidget::reset_unit_buttons(const Player& player) const
{
    m_villager_button->set_disable(false);
    m_villager_button->set_background_texture(ResourceManager::get_sprite(sprite_names::villager));
    m_soldier_button->set_disable(false);
    m_soldier_button->set_background_texture(ResourceManager::get_sprite(sprite_names::soldier));
    m_knight_button->set_disable(false);
    m_knight_button->set_background_texture(ResourceManager::get_sprite(sprite_names::knight));
    m_tower_button->set_disable(false);
    switch (player.id)
    {
    case 1:
        m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower1));
        break;
    case 2:
        m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower2));
        break;
    case 3:
        m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower3));
        break;
    case 4:
        m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower4));
        break;
    }
}

void PlayerInfoWidget::update_buyable_entities_button(const Player& player, const std::vector<HexEntity>& not_buyable_entities) const
{
    for (const HexEntity& entity : not_buyable_entities)
    {
        switch (entity)
        {
        case HexEntity::Villager:
            m_villager_button->set_disable(true);
            m_villager_button->set_background_texture(ResourceManager::get_sprite(sprite_names::villager_darkened));
            break;
        case HexEntity::Soldier:
            m_soldier_button->set_disable(true);
            m_soldier_button->set_background_texture(ResourceManager::get_sprite(sprite_names::soldier_darkened));
            break;
        case HexEntity::Knight:
            m_knight_button->set_disable(true);
            m_knight_button->set_background_texture(ResourceManager::get_sprite(sprite_names::knight_darkened));
            break;
        case HexEntity::Tower:
            m_tower_button->set_disable(true);
            switch (player.id)
            {
            case 1:
                m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower1_darkened));
                break;
            case 2:
                m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower2_darkened));
                break;
            case 3:
                m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower3_darkened));
                break;
            case 4:
                m_tower_button->set_background_texture(ResourceManager::get_sprite(sprite_names::tower4_darkened));
                break;
            }
            break;
        }
    }
}
