template<typename T>
template<typename U>
constexpr Vector2<U> Vector2<T>::cast() const
{
    return { static_cast<U>(x), static_cast<U>(y) };
}

template<typename T>
template<typename U>
constexpr Vector2<T>::operator Vector2<U>() const
{
    return { static_cast<U>(x), static_cast<U>(y) };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator+(const Vector2& other) const
{
    return { x + other.x, y + other.y };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator-(const Vector2& other) const
{
    return { x - other.x, y - other.y };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator/(const Vector2& other) const
{
    return { x / other.x, y / other.y };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator*(const Vector2& other) const
{
    return { x * other.x, y * other.y };
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
constexpr Vector2<T>& Vector2<T>::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator*(T factor) const
{
    return { x * factor, y * factor };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator/(T factor) const
{
    return { x / factor, y / factor };
}

template<typename T>
Vector2<T> constexpr Vector2<T>::operator-(T factor) const
{
    return { x - factor, y - factor };
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(T factor)
{
    x *= factor;
    y *= factor;
    return *this;
}

template<typename T>
template<typename U>
Vector2<T> constexpr Vector2<T>::operator/(U factor) const
{
    return { x / static_cast<U>(factor), y / static_cast<U>(factor) };
}