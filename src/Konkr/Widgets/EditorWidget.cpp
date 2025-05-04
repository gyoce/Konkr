#include "Konkr/Widgets/EditorWidget.hpp"

#include "Engine/Managers/ResourceManager.hpp"
#include "Engine/Utils/Logs.hpp"
#include "Konkr/Utils/Constants.hpp"
#include "Konkr/Models/Units/Villager.hpp"
#include "Konkr/Models/Units/Soldier.hpp"
#include "Konkr/Models/Units/Knight.hpp"
#include "Konkr/Models/Buildings/Tower.hpp"
#include "Konkr/Models/Buildings/Castle.hpp"

const std::vector<std::string> EditorWidget::s_type_options =
{
    "Territory",
    "Decoration"
};

const std::vector<std::string> EditorWidget::s_unit_options =
{
    "None",
    "Villager",
    "Soldier",
    "Knight"
};

const std::vector<std::string> EditorWidget::s_building_options =
{
    "None",
    "City Hall",
    "Tower"
};

const std::vector<std::string> EditorWidget::s_player_options =
{
    "None",
    "Player 1",
    "Player 2",
    "Player 3",
    "Player 4"
};

EditorWidget::EditorWidget()
{
    GuiPanel::set_stretch({ 1.0f, 0.15f });
    GuiPanel::set_background_color({ 0, 0, 0, 64 });
    GuiPanel::set_interactable(true);

    m_editor_layout = std::make_shared<GuiHorizontalLayout>();
    m_editor_layout->set_horizontal_start(Horizontal::Left);
    m_editor_layout->set_stretch({ 1.0f, 1.0f });
    m_editor_layout->set_padding_between_items({ 25, 0 });

    init_controls_layout();
    init_selectable_options();

    GuiPanel::set_layout(m_editor_layout);
}

void EditorWidget::init_controls_layout() const
{
    const GuiVerticalLayout::SP controls_layout = std::make_shared<GuiVerticalLayout>();
    controls_layout->set_stretch({ 0.15f, 1.0f });
    controls_layout->set_padding_between_items({ 0, 5 });

    // "Place" + Mouse left 
    const GuiHorizontalLayout::SP place_panel = std::make_shared<GuiHorizontalLayout>();
    place_panel->set_stretch({ 1.0f, 0.4f });
    place_panel->set_padding_between_items({ 10, 0 });

    const GuiImage::SP mouse_left_img = std::make_shared<GuiImage>();
    mouse_left_img->set_image(ResourceManager::get_sprite(sprite_names::ui_mouse_left));
    mouse_left_img->set_stretch({ 0.15f, 0.8f });
    place_panel->add_widget(mouse_left_img);

    const GuiText::SP place_text = std::make_shared<GuiText>();
    place_text->set_text("Place");
    place_text->set_stretch({ 0.6f, 1.0f });
    place_text->set_horizontal_align(Horizontal::Left);
    place_panel->add_widget(place_text);
    controls_layout->add_layout(place_panel);

    // "Remove" + Mouse right
    const GuiHorizontalLayout::SP remove_panel = std::make_shared<GuiHorizontalLayout>();
    remove_panel->set_stretch({ 1.0f, 0.4f });
    remove_panel->set_padding_between_items({ 10, 0 });

    const GuiImage::SP mouse_right_img = std::make_shared<GuiImage>();
    mouse_right_img->set_image(ResourceManager::get_sprite(sprite_names::ui_mouse_right));
    mouse_right_img->set_stretch({ 0.15f, 0.8f });
    remove_panel->add_widget(mouse_right_img);

    const GuiText::SP remove_text = std::make_shared<GuiText>();
    remove_text->set_text("Remove");
    remove_text->set_stretch({ 0.6f, 1.0f });
    remove_text->set_horizontal_align(Horizontal::Left);
    remove_panel->add_widget(remove_text);
    controls_layout->add_layout(remove_panel);

    m_editor_layout->add_layout(controls_layout);
}

void EditorWidget::init_selectable_options()
{
    static constexpr Vector2f stretch_selectable_options{ 0.18f, 0.9f };

    m_selectable_options_type = std::make_shared<SelectableOptions>();
    m_selectable_options_type->set_stretch(stretch_selectable_options);
    m_selectable_options_type->set_title("Type");
    m_selectable_options_type->set_options(s_type_options);
    m_selectable_options_type->set_option_selected_callback([this](const int index) { on_type_option_selected(index); });
    m_editor_layout->add_widget(m_selectable_options_type);

    m_selectable_options_unit = std::make_shared<SelectableOptions>();
    m_selectable_options_unit->set_stretch(stretch_selectable_options);
    m_selectable_options_unit->set_title("Unit");
    m_selectable_options_unit->set_options(s_unit_options);
    m_selectable_options_unit->set_option_selected_callback([this](const int index) { on_unit_option_selected(index); });
    m_editor_layout->add_widget(m_selectable_options_unit);

    m_selectable_options_building = std::make_shared<SelectableOptions>();
    m_selectable_options_building->set_stretch(stretch_selectable_options);
    m_selectable_options_building->set_title("Building");
    m_selectable_options_building->set_options(s_building_options);
    m_selectable_options_building->set_option_selected_callback([this](const int index) { on_building_option_selected(index); });
    m_editor_layout->add_widget(m_selectable_options_building);

    m_selectable_options_player = std::make_shared<SelectableOptions>();
    m_selectable_options_player->set_stretch(stretch_selectable_options);
    m_selectable_options_player->set_title("Player");
    m_selectable_options_player->set_options(s_player_options);
    m_selectable_options_player->set_option_selected_callback([this](const int index) { on_player_option_selected(index); });
    m_editor_layout->add_widget(m_selectable_options_player);
}

void EditorWidget::on_type_option_selected(const int index)
{
    if (index == 1) // Decoration selected
    {
        m_hex_option.type = HexType::Decoration;
        m_hex_option.entity = nullptr;
        m_hex_option.player = 0;
        m_selectable_options_unit->set_selected(0); // None
        m_selectable_options_building->set_selected(0); // None
        m_selectable_options_player->set_selected(0); // None
    }
    else
        m_hex_option.type = HexType::Territory;

    if (m_on_options_changed)
        m_on_options_changed(m_hex_option);
}

void EditorWidget::on_player_option_selected(const int index)
{
    m_hex_option.player = index;
    m_hex_option.type = HexType::Territory;
    
    m_selectable_options_type->set_selected(0); // Territory
    if (index == 0)
    {
        m_selectable_options_building->set_selected(0); // None
        m_selectable_options_unit->set_selected(0); // None
        m_hex_option.entity = nullptr;
    }        

    if (m_on_options_changed)
        m_on_options_changed(m_hex_option);
}

void EditorWidget::on_unit_option_selected(const int index)
{
    m_hex_option.type = HexType::Territory;

    switch (index)
    {
    default:
    case 0:
        m_hex_option.entity = nullptr;
        break;
    case 1:
        m_hex_option.entity = std::make_shared<Villager>();
        break;
    case 2:
        m_hex_option.entity = std::make_shared<Soldier>();
        break;
    case 3:
        m_hex_option.entity = std::make_shared<Knight>();
        break;
    }

    if (index != 0) // Not none
    {
        m_selectable_options_type->set_selected(0); // Territory
        m_selectable_options_building->set_selected(0); // None
    }

    if (m_on_options_changed)
        m_on_options_changed(m_hex_option);
}

void EditorWidget::on_building_option_selected(const int index)
{
    m_hex_option.type = HexType::Territory;

    switch (index)
    {
    default:
    case 0:
        m_hex_option.entity = nullptr;
        break;
    case 1:
        m_hex_option.entity = std::make_shared<Castle>();;
        break;
    case 2:
        m_hex_option.entity = std::make_shared<Tower>();;
        break;
    }

    if (index != 0) // Not none
    {
        m_selectable_options_type->set_selected(0); // Territory
        m_selectable_options_unit->set_selected(0); // None
        if (m_hex_option.player == 0)
        {
            m_selectable_options_player->set_selected(1); // At least player 1
            m_hex_option.player = 1;
        }
    }

    if (m_on_options_changed)
        m_on_options_changed(m_hex_option);
}
