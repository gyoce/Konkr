#include "Engine/Utils/Utils.hpp"

std::string engine_utils::keyboard_key_to_string(const Keyboard::Key key)
{
    switch (key)
    {
    case Keyboard::Key::A:
        return "A";
    case Keyboard::Key::B:
        return "B";
    case Keyboard::Key::C:
        return "C";
    case Keyboard::Key::D:
        return "D";
    case Keyboard::Key::E:
        return "E";
    case Keyboard::Key::F:
        return "F";
    case Keyboard::Key::G:
        return "G";
    case Keyboard::Key::H:
        return "H";
    case Keyboard::Key::I:
        return "I";
    case Keyboard::Key::J:
        return "J";
    case Keyboard::Key::K:
        return "K";
    case Keyboard::Key::L:
        return "L";
    case Keyboard::Key::M:
        return "M";
    case Keyboard::Key::N:
        return "N";
    case Keyboard::Key::O:
        return "O";
    case Keyboard::Key::P:
        return "P";
    case Keyboard::Key::Q:
        return "Q";
    case Keyboard::Key::R:
        return "R";
    case Keyboard::Key::S:
        return "S";
    case Keyboard::Key::T:
        return "T";
    case Keyboard::Key::U:
        return "U";
    case Keyboard::Key::V:
        return "V";
    case Keyboard::Key::W:
        return "W";
    case Keyboard::Key::X:
        return "X";
    case Keyboard::Key::Y:
        return "Y";
    case Keyboard::Key::Z:
        return "Z";
    case Keyboard::Key::Num0:
        return "0";
    case Keyboard::Key::Num1:
        return "1";
    case Keyboard::Key::Num2:
        return "2";
    case Keyboard::Key::Num3:
        return "3";
    case Keyboard::Key::Num4:
        return "4";
    case Keyboard::Key::Num5:
        return "5";
    case Keyboard::Key::Num6:
        return "6";
    case Keyboard::Key::Num7:
        return "7";
    case Keyboard::Key::Num8:
        return "8";
    case Keyboard::Key::Num9:
        return "9";
    case Keyboard::Key::Left:
        return "Left";
    case Keyboard::Key::Right:
        return "Right";
    case Keyboard::Key::Up:
        return "Up";
    case Keyboard::Key::Down:
        return "Down";
    case Keyboard::Key::L_Alt:
        return "Left Alt";
    case Keyboard::Key::R_Alt:
        return "Right Alt";
    case Keyboard::Key::L_Ctrl:
        return "Left Control";
    case Keyboard::Key::R_Ctrl:
        return "Right Control";
    case Keyboard::Key::Backspace:
        return "Backspace";
    case Keyboard::Key::Escape:
        return "Escape";
    case Keyboard::Key::L_Shift:
        return "Left Shift";
    case Keyboard::Key::R_Shift:
        return "Right Shift";
    case Keyboard::Key::NotRecognized:
        return "Not recognized";
    default:
        return "Unknown";
    }
}

std::string engine_utils::mouse_button_to_string(const Mouse::Button button)
{
    switch (button)
    {
    case Mouse::Button::Left:
        return "Left";
    case Mouse::Button::Right:
        return "Right";
    case Mouse::Button::Middle:
        return "Middle";
    case Mouse::NotRecognized:
        return "Not recognized";
    default:
        return "Unknown";
    }
}
