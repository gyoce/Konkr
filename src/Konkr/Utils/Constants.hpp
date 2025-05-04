#ifndef KONKR_CONSTANTS_HPP
#define KONKR_CONSTANTS_HPP

#include <string>
#include <unordered_map>
#include <cstdint>

#include "Engine/Graphics/Color.hpp"
#include "Engine/Math/Math.hpp"
#include "Konkr/Hex/HexEnums.hpp"

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define RES_PATH std::string(macro_xstr(DEF_RES_PATH))

enum class SpriteType : std::uint8_t
{
    Tile0,
    Tile1,
    Tile1_Decoration1,
    Tile1_Decoration2,
    Tower1,
    CityHall1,
    Tile2,
    Tower2,
    CityHall2,
    Tile3,
    Tower3,
    CityHall3,
    Tile4,
    Tower4,
    CityHall4,
    Villager,
    Soldier,
    Knight,
    Hero,
    Highlighted,
    Bandit,
    None,
};

namespace sprite_names
{
    inline const std::string tile0 = "Tile0";
    inline const std::string tile1 = "Tile1";
    inline const std::string tile1_decoration1 = "Tile1_Decoration1";
    inline const std::string tile1_decoration2 = "Tile1_Decoration2";
    inline const std::string tower1 = "Tower1";
    inline const std::string tower1_darkened = "Tower1_Darkened";
    inline const std::string city_hall1 = "CityHall1";
    inline const std::string tile2 = "Tile2";
    inline const std::string tower2 = "Tower2";
    inline const std::string tower2_darkened = "Tower2_Darkened";
    inline const std::string city_hall2 = "CityHall2";
    inline const std::string tile3 = "Tile3";
    inline const std::string tower3 = "Tower3";
    inline const std::string tower3_darkened = "Tower3_Darkened";
    inline const std::string city_hall3 = "CityHall3";
    inline const std::string tile4 = "Tile4";
    inline const std::string tower4 = "Tower4";
    inline const std::string tower4_darkened = "Tower4_Darkened";
    inline const std::string city_hall4 = "CityHall4";
    inline const std::string villager = "Villager";
    inline const std::string villager_darkened = "Villager_Darkened";
    inline const std::string soldier = "Soldier";
    inline const std::string soldier_darkened = "Soldier_Darkened";
    inline const std::string knight = "Knight";
    inline const std::string knight_darkened = "Knight_Darkened";
    inline const std::string hero = "Hero";
    inline const std::string bandit = "Bandit";
    inline const std::string hightlighted = "Highlighted";
    inline const std::string fence_NW = "Fence_NW";
    inline const std::string fence_NE = "Fence_NE";
    inline const std::string fence_SE = "Fence_SE";
    inline const std::string fence_SW = "Fence_SW";
    inline const std::string fence_W = "Fence_W";
    inline const std::string fence_E = "Fence_E";

    inline const std::string ui_red_button_depth = "UiRedButtonDepth";
    inline const std::string ui_red_button = "UiRedButton";
    inline const std::string ui_red_button_hovered = "UiRedButtonHovered";
    inline const std::string ui_blue_button_depth = "UiBlueButtonDepth";
    inline const std::string ui_blue_button = "UiBlueButton";
    inline const std::string ui_blue_button_hovered = "UiBlueButtonHovered";
    inline const std::string ui_grey_panel = "UiGreyPanel";
    inline const std::string ui_cursor_idle = "UiCursorIdle";
    inline const std::string ui_cursor_clickable = "UiCursorClickable";
    inline const std::string ui_cursor_dragging = "UiCursorDragging";
    inline const std::string ui_cursor_disable = "UiCursorDisable";
    inline const std::string ui_gearwheel = "UiGearwheel";
    inline const std::string ui_gearwheel_hovered = "UiGearwheelHovered";
    inline const std::string ui_red_cross = "UiRedCross";
    inline const std::string ui_red_cross_hovered = "UiRedCrossHovered";
    inline const std::string ui_mouse = "UiMouse";
    inline const std::string ui_mouse_left = "UiMouseLeft";
    inline const std::string ui_mouse_right = "UiMouseRight";
    inline const std::string ui_arrow_right = "UiArrowRight";
    inline const std::string ui_arrow_right_hovered = "UiArrowRightHovered";
    inline const std::string ui_arrow_left = "UiArrowLeft";
    inline const std::string ui_arrow_left_hovered = "UiArrowLeftHovered";
    inline const std::string ui_burger_menu = "UiBurgerMenu";
    inline const std::string ui_burger_menu_hovered = "UiBurgerMenuHovered";
    inline const std::string ui_money_idle = "UiMoneyIdle";
    inline const std::string ui_money_incoming = "UiMoneyIncoming";
    inline const std::string ui_money_outgoing = "UiMoneyOutgoing";
    inline const std::string ui_green_cross = "UiGreenCross";

    const std::string& from_sprite_type(SpriteType type);
    const std::string& from_hex_direction(HexDirection direction);
} // namespace sprite_names

namespace constants
{
    /// Path to resources
    inline const std::string main_font = "MainFont";
    inline const std::string path_font = RES_PATH + "/fonts/PoetsenOne-Regular.ttf";
    inline const std::string path_game_sprite_sheet = RES_PATH + "/imgs/GameSpriteSheet.png";
    inline const std::string path_ui_sprite_sheet = RES_PATH + "/imgs/UiSpriteSheet.png";
    inline const std::string path_maps = RES_PATH + "/maps/";

    /// SceneManager variables
    inline const std::string menu_map_selected = "menu_map_selected";
    inline const std::string menu_map_new = "menu_map_new";

    /// Game variables
    inline constexpr Color background_color { 99, 197, 207, 255 };
    inline constexpr float initial_hex_size = 50.0f;
    inline constexpr float max_hex_size = 150.0f;
    inline constexpr float min_hex_size = 10.0f;
    inline constexpr float hex_size_step = 5.0f;
    inline constexpr float hex_map_move_velocity = 300.0f;
    inline constexpr float building_sprite_factor = 1.5f;
    inline constexpr float unit_sprite_factor = 1.0f;

    inline constexpr float bounce_speed = 5.0f;
    inline constexpr float bounce_amplitude = 15.0f;

    inline constexpr int default_cost_per_turn = 0;
    inline constexpr int bandit_level = 0;
    inline constexpr int villager_level = 1;
    inline constexpr int villager_price = 10;
    inline constexpr int villager_cost_per_turn = 2;
    inline constexpr int soldier_level = 2;
    inline constexpr int soldier_price = 20;
    inline constexpr int soldier_cost_per_turn = 6;
    inline constexpr int knight_level = 3;
    inline constexpr int knight_price = 40;
    inline constexpr int knight_cost_per_turn = 18;
    inline constexpr int hero_level = 4;
    inline constexpr int hero_cost_per_turn = 54;
    inline constexpr int tower_level = 2;
    inline constexpr int tower_price = 20;
    inline constexpr int tower_cost_per_turn = 2;
    inline constexpr int castle_level = 1;
    inline constexpr int castle_cost_per_turn = 2;

    inline std::array player_colors
    {
        Color { 39 , 174, 96 , 255 },
        Color { 156, 99 , 85 , 255 },
        Color { 39 , 174, 134, 255 },
        Color { 173, 174, 39 , 255 }
    };

    float get_sprite_decoration_factor(SpriteType sprite);

    inline const std::unordered_map<std::string, std::pair<Recti, bool>> game_sprite_rects
    {
          { sprite_names::tile0,             { Recti {4  , 290, 120, 140}, false } },
          { sprite_names::tile1,             { Recti {4  , 2  , 120, 140}, false } },
          { sprite_names::tile1_decoration1, { Recti {132, 2  , 120, 140}, false } },
          { sprite_names::tile1_decoration2, { Recti {260, 2  , 120, 140}, false } },
          { sprite_names::tower1,            { Recti {0  , 576, 48 , 84 }, true  } },
          { sprite_names::tower1_darkened,   { Recti {192, 576, 48 , 84 }, true  } },
          { sprite_names::city_hall1,        { Recti {0  , 672, 75 , 75 }, true  } },
          { sprite_names::tile2,             { Recti {4  , 146, 120, 140}, false } },
          { sprite_names::tower2,            { Recti {48 , 576, 48 , 84 }, true  } },
          { sprite_names::tower2_darkened,   { Recti {240, 576, 48 , 84 }, true  } },
          { sprite_names::city_hall2,        { Recti {80 , 672, 75 , 75 }, true  } },
          { sprite_names::tile3,             { Recti {132, 146, 120, 140}, false } },
          { sprite_names::tower3,            { Recti {96 , 576, 48 , 84 }, true  } },
          { sprite_names::tower3_darkened,   { Recti {240, 576, 48 , 84 }, true  } },
          { sprite_names::city_hall3,        { Recti {160, 672, 75 , 75 }, true  } },
          { sprite_names::tile4,             { Recti {260, 146, 120, 140}, false } },
          { sprite_names::tower4,            { Recti {144, 576, 48 , 84 }, true  } },
          { sprite_names::tower4_darkened,   { Recti {336, 576, 48 , 84 }, true  } },
          { sprite_names::city_hall4,        { Recti {240, 672, 75 , 75 }, true  } },
          { sprite_names::villager,          { Recti {0  , 752, 64 , 80 }, true  } },
          { sprite_names::villager_darkened, { Recti {0  , 832, 64 , 80 }, true  } },
          { sprite_names::soldier,           { Recti {80 , 752, 64 , 80 }, true  } },
          { sprite_names::soldier_darkened,  { Recti {80 , 832, 64 , 80 }, true  } },
          { sprite_names::knight,            { Recti {160, 752, 80 , 80 }, true  } },
          { sprite_names::knight_darkened,   { Recti {160, 832, 80 , 80 }, true  } },
          { sprite_names::hero,              { Recti {256, 752, 76 , 80 }, true  } },
          { sprite_names::bandit,            { Recti {352, 752, 69 , 80 }, true  } },
          { sprite_names::hightlighted,      { Recti {644, 354, 120, 140}, true  } },
          { sprite_names::fence_NW,          { Recti {388, 2  , 120, 140}, true  } },
          { sprite_names::fence_NE,          { Recti {516, 2  , 120, 140}, true  } },
          { sprite_names::fence_W,           { Recti {644, 2  , 120, 140}, true  } },
          { sprite_names::fence_SE,          { Recti {388, 146, 120, 140}, true  } },
          { sprite_names::fence_SW,          { Recti {516, 146, 120, 140}, true  } },
          { sprite_names::fence_E,           { Recti {644, 146, 120, 140}, true  } },
    };

    inline const std::unordered_map<std::string, std::pair<Recti, bool>> ui_sprite_rects = 
    {
        { sprite_names::ui_red_button_depth,        { Recti {0  , 0  , 192, 64 }, true } },
        { sprite_names::ui_red_button,              { Recti {192, 0  , 192, 64 }, true } },
        { sprite_names::ui_red_button_hovered,      { Recti {192, 64 , 192, 64 }, true } },
        { sprite_names::ui_blue_button_depth,       { Recti {0  , 128, 192, 64 }, true } },
        { sprite_names::ui_blue_button,             { Recti {192, 128, 192, 64 }, true } },
        { sprite_names::ui_blue_button_hovered,     { Recti {192, 192, 192, 64 }, true } },
        { sprite_names::ui_grey_panel,              { Recti {512, 0  , 256, 144}, true } },
        { sprite_names::ui_cursor_idle,             { Recti {768, 0  , 64 , 64 }, true } },
        { sprite_names::ui_cursor_clickable,        { Recti {832, 0  , 64 , 64 }, true } },
        { sprite_names::ui_cursor_dragging,         { Recti {896, 0  , 64 , 64 }, true } },
        { sprite_names::ui_cursor_disable,          { Recti {960, 0  , 64 , 64 }, true } },
        { sprite_names::ui_gearwheel,               { Recti {768, 64 , 64 , 64 }, true } },
        { sprite_names::ui_gearwheel_hovered,       { Recti {832, 64 , 64 , 64 }, true } },
        { sprite_names::ui_red_cross,               { Recti {768, 128, 64 , 64 }, true } },
        { sprite_names::ui_red_cross_hovered,       { Recti {832, 128, 64 , 64 }, true } },
        { sprite_names::ui_mouse,                   { Recti {774, 196, 68 , 88 }, true } },
        { sprite_names::ui_mouse_left,              { Recti {854, 196, 68 , 88 }, true } },
        { sprite_names::ui_mouse_right,             { Recti {934, 196, 68 , 88 }, true } },
        { sprite_names::ui_arrow_right,             { Recti {772, 288, 40 , 64 }, true } },
        { sprite_names::ui_arrow_right_hovered,     { Recti {820, 288, 40 , 64 }, true } },
        { sprite_names::ui_arrow_left,              { Recti {868, 288, 40 , 64 }, true } },
        { sprite_names::ui_arrow_left_hovered,      { Recti {916, 288, 40 , 64 }, true } },
        { sprite_names::ui_burger_menu,             { Recti {772, 352, 72 , 64 }, true } },
        { sprite_names::ui_burger_menu_hovered,     { Recti {852, 352, 72 , 64 }, true } },
        { sprite_names::ui_money_idle,              { Recti {704, 416, 96 , 112}, true } },
        { sprite_names::ui_money_incoming,          { Recti {912, 416, 112, 112}, true } },
        { sprite_names::ui_money_outgoing,          { Recti {800, 416, 112, 112}, true } },
        { sprite_names::ui_green_cross,             { Recti {390, 134, 52 , 52 }, true } },
    };

    // popup variables
    inline constexpr Color info_text_color{200, 200, 255, 255};
    inline constexpr Color error_text_color{255, 100, 100, 255};
    inline constexpr Color success_text_color{100, 255, 100, 255};
    inline constexpr Color warning_text_color{255, 255, 0, 255};

    inline constexpr Color info_bg_color{ 0, 0, 60, 200 };
    inline constexpr Color error_bg_color{60, 0, 0, 200};
    inline constexpr Color success_bg_color{0, 60, 0, 200};
    inline constexpr Color warning_bg_color{60, 60, 0, 200};

    inline constexpr float default_total_duration{ 3.0f };
    inline constexpr float default_fade_duration{ 0.5f };
    inline constexpr float infinite_total_duration{ 0.0f };

} // namespace constants

#endif // KONKR_CONSTANTS_HPP