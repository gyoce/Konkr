#ifndef KONKR_EDITOR_WIDGET_HPP
#define KONKR_EDITOR_WIDGET_HPP

#include "Engine/Ui/Gui.hpp"
#include "Konkr/Hex/HexEnums.hpp"
#include "Konkr/Models/Entity.hpp"
#include "Konkr/Widgets/SelectableOptions.hpp"

struct HexOption
{
    HexType type = HexType::Territory;
    Entity::SP entity;
    int player = 0;
};

class EditorWidget final : public GuiPanel
{
public:
    EditorWidget();

    void set_on_options_changed(std::function<void(const HexOption&)> on_options_changed) { m_on_options_changed = std::move(on_options_changed);  }

    using SP = std::shared_ptr<EditorWidget>;

private:
    void init_controls_layout() const;
    void init_selectable_options();

    void on_player_option_selected(int index);
    void on_type_option_selected(int index);
    void on_unit_option_selected(int index);
    void on_building_option_selected(int index);

    std::function<void(HexOption&)> m_on_options_changed = nullptr;

    GuiHorizontalLayout::SP m_editor_layout = nullptr;
    SelectableOptions::SP m_selectable_options_type = nullptr;
    SelectableOptions::SP m_selectable_options_unit = nullptr;
    SelectableOptions::SP m_selectable_options_building = nullptr;
    SelectableOptions::SP m_selectable_options_player = nullptr;

    HexOption m_hex_option;

    static const std::vector<std::string> s_type_options;
    static const std::vector<std::string> s_unit_options;
    static const std::vector<std::string> s_building_options;
    static const std::vector<std::string> s_player_options;
};

#endif // KONKR_EDITOR_WIDGET_HPP