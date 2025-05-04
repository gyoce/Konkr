#ifndef ENGINE_VECTOR2_HPP
#define ENGINE_VECTOR2_HPP

#include <cmath>

template<typename T>
class Vector2
{
public:
    constexpr Vector2() = default;
    constexpr Vector2(T x, T y) : x(x), y(y){}
    template <typename U> constexpr Vector2(U x, U y) : x(static_cast<T>(x)), y(static_cast<T>(y)){}

    T x{};
    T y{};

    template<typename U> [[nodiscard]] constexpr Vector2<U> cast() const;
    template<typename U> constexpr explicit operator Vector2<U>() const;

    constexpr Vector2& abs() { x = std::abs(x); y = std::abs(y); return *this; }

    constexpr Vector2 operator+(const Vector2& other) const;
    constexpr Vector2 operator-(const Vector2& other) const;
    constexpr Vector2 operator/(const Vector2& other) const;
    constexpr Vector2 operator*(const Vector2& other) const;
    constexpr Vector2& operator+=(const Vector2& other);
    constexpr Vector2& operator-=(const Vector2& other);
    constexpr Vector2 operator*(T factor) const;
    constexpr Vector2 operator/(T factor) const;
    constexpr Vector2 operator-(T factor) const;
    constexpr Vector2& operator*=(T factor);
    template<typename U> constexpr Vector2 operator/(U factor) const;

    constexpr bool operator==(const Vector2& other) const = default;
    constexpr bool operator!=(const Vector2& other) const = default;
    constexpr bool operator<(const Vector2& other) const { return x < other.x && y < other.y; }

    static const Vector2 Zero;
    static const Vector2 One;
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;

template<> inline constexpr Vector2f Vector2<float>::Zero{ 0, 0 };
template<> inline constexpr Vector2i Vector2<int>::Zero{ 0, 0 };
template<> inline constexpr Vector2f Vector2<float>::One{ 1, 1 };
template<> inline constexpr Vector2i Vector2<int>::One{ 1, 1 };

#include "Engine/Math/Vector2.inl"

#endif // ENGINE_VECTOR2_HPP