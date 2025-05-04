#include "Konkr/Konkr.hpp"

#include "Konkr/Scenes/MenuScene.hpp"
#include "Konkr/Scenes/GameScene.hpp"
#include "Konkr/Scenes/EditorScene.hpp"
#include "Konkr/Utils/Constants.hpp"
#include "Engine/Utils/Timer.hpp"

Konkr::Konkr()
{
    m_game_sprite_sheet = Texture::load_image(constants::path_game_sprite_sheet);
    m_ui_sprite_sheet = Texture::load_image(constants::path_ui_sprite_sheet);

    m_resource_manager->load_sprites(m_game_sprite_sheet, constants::game_sprite_rects);
    m_resource_manager->load_sprites(m_ui_sprite_sheet, constants::ui_sprite_rects);
    m_resource_manager->load_font(constants::main_font, constants::path_font);
    m_resource_manager->set_main_font(ResourceManager::get_font(constants::main_font));

    Cursor::register_cursor(Cursor::Type::Idle, ResourceManager::get_sprite(sprite_names::ui_cursor_idle));
    Cursor::register_cursor(Cursor::Type::Clickable, ResourceManager::get_sprite(sprite_names::ui_cursor_clickable));
    Cursor::register_cursor(Cursor::Type::Dragging, ResourceManager::get_sprite(sprite_names::ui_cursor_dragging));
    Cursor::register_cursor(Cursor::Type::Disable, ResourceManager::get_sprite(sprite_names::ui_cursor_disable));

    m_scene_manager->register_scene<MenuScene>();
    m_scene_manager->register_scene<GameScene>();
    m_scene_manager->register_scene<EditorScene>();
    SceneManager::change_scene(0);

    m_timer.set_delay(1.0f);
    m_timer.set_callback([]
    {
        WindowManager::change_title(std::format("Konkr | {} fps", static_cast<int>(1.0f / TimeManager::get_delta_time())));
    });

    EventManager::register_on_key_press_event([this](const Event::KeyboardButton& event) { on_key_pressed(event); });
}

void Konkr::frame()
{
    m_timer.update();
}

void Konkr::on_key_pressed(const Event::KeyboardButton& event)
{
    if (event.key == Keyboard::Key::R_Alt)
        GuiManager::debug_mode = !GuiManager::debug_mode;
}
