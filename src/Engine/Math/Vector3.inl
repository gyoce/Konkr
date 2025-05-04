template<typename T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3& other) const
{
    return { x + other.x, y + other.y, z + other.z };
}