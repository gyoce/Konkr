#ifndef ENGINE_RECT_HPP
#define ENGINE_RECT_HPP

template<typename T>
class Rect
{
public:
    constexpr Rect() = default;
    constexpr Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
    template<typename U> constexpr Rect(U x, U y, U w, U h) : x(static_cast<T>(x)), y(static_cast<T>(y)), w(static_cast<T>(w)), h(static_cast<T>(h)) {}

    T x{}, y{}, w{}, h{};
};

using Recti = Rect<int>;
using Rectf = Rect<float>;

#endif // ENGINE_RECT_HPP