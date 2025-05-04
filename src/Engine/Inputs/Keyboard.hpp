#ifndef ENGINE_KEYBOARD_HPP
#define ENGINE_KEYBOARD_HPP

#include <cstdint>

class Keyboard
{
public:
    Keyboard() = delete;

    enum class Key : std::uint8_t
    {
        NotRecognized,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Left,
        Right,
        Up,
        Down,
        L_Alt,
        R_Alt,
        L_Ctrl,
        R_Ctrl,
        Escape,
        Backspace,
        L_Shift,
        R_Shift,
        None
    };

    static bool is_key_pressed(Key key);
};

#endif // ENGINE_KEYBOARD_HPP