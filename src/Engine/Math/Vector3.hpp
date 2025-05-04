#ifndef ENGINE_VECTOR3_HPP
#define ENGINE_VECTOR3_HPP

template<typename T>
class Vector3
{
public:
    constexpr Vector3() = default;
    constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) { }

    T x{};
    T y{};
    T z{};

    constexpr Vector3 operator+(const Vector3& other) const;
    constexpr bool operator==(const Vector3& other) const = default;

    static const Vector3 Zero;
    static const Vector3 One;
};

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

template<> inline constexpr Vector3f Vector3<float>::Zero{ 0, 0, 0 };
template<> inline constexpr Vector3i Vector3<int>::Zero{ 0, 0, 0 };
template<> inline constexpr Vector3f Vector3<float>::One{ 1, 1, 1 };
template<> inline constexpr Vector3i Vector3<int>::One{ 1, 1, 1 };

#include "Engine/Math/Vector3.inl"

#endif // ENGINE_VECTOR3_HPP