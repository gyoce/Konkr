#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <concepts>

#include "Engine/Inputs/Keyboard.hpp"
#include "Engine/Inputs/Mouse.hpp"

namespace engine_utils
{
    std::string keyboard_key_to_string(Keyboard::Key key);
    std::string mouse_button_to_string(Mouse::Button button);

    template<class T, std::predicate<T&> Pred> bool contains(const std::vector<T>& vec, Pred pred)
    {
        return std::ranges::find_if(vec, pred) != vec.end();
    }
} // namespace utils

#endif // ENGINE_UTILS_HPP