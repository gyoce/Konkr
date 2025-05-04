#ifndef KONKR_GAME_HPP
#define KONKR_GAME_HPP

#include "Engine/Game.hpp"
#include "Engine/Utils/Timer.hpp"

class Konkr final : public Game
{
public:
    Konkr();

    void frame() override;

private:
    static void on_key_pressed(const Event::KeyboardButton& event);

    Texture::SP m_game_sprite_sheet = nullptr;
    Texture::SP m_ui_sprite_sheet = nullptr;
    Timer m_timer;
};

#endif // KONKR_GAME_HPP