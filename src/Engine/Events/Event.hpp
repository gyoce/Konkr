#ifndef ENGINE_EVENT_HPP
#define ENGINE_EVENT_HPP

#include <string>
#include <variant>

#include "Engine/Math/Math.hpp"
#include "Engine/Inputs/Mouse.hpp"
#include "Engine/Inputs/Keyboard.hpp"

class Event
{
public:
    Event() = default;
    template<typename T> explicit Event(T data);

    enum class State : std::uint8_t
    {
        Pressed,
        Released
    };

    struct MouseButton
    {
        Mouse::Button button; // The button that was pressed or released
        State state;          // Pressed or Released
        Vector2i position;    // The position of the mouse when the button was pressed or released
    };

    struct MouseWheel
    {
        int vertical_delta;   // if < 0, scroll down; if > 0, scroll up
        int horizontal_delta; // if < 0, scroll left; if > 0, scroll right
    };

    struct MouseMove
    {
        Vector2i position; // The new position of the mouse
    };

    struct KeyboardButton
    {
        Keyboard::Key key; // The key that was pressed or released
        State state;       // Pressed or Released
    };

    struct WindowResize
    {
        Vector2i size; // The new size of the window
    };

    struct TextInput
    {
        std::string text; // The text that was input
    };

    template<typename T> [[nodiscard]] constexpr bool is() const { return std::holds_alternative<T>(m_data); }
    template<typename T> const T& get() const;
    template<typename T> void reset();

private:
    std::variant<
        MouseButton,
        MouseWheel,
        MouseMove,
        KeyboardButton,
        WindowResize,
        TextInput
    > m_data;

    template <typename T, typename... Ts>
    [[nodiscard]] static constexpr bool is_in_parameter_pack(const std::variant<Ts...>*)
    {
        return std::disjunction_v<std::is_same<T, Ts>...>;
    }

    template<typename T>
    static constexpr bool is_event_subtype = is_in_parameter_pack<T>(static_cast<decltype(&m_data)>(nullptr));
};

#include "Engine/Events/Event.inl"

#endif // ENGINE_EVENT_HPP