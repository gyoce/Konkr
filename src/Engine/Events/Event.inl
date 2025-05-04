template<typename T>
Event::Event(T data)
    : m_data(std::move(data))
{
    static_assert(is_event_subtype<T>, "T is not a valid type for Event");
}

template<typename T>
const T& Event::get() const
{
    static_assert(is_event_subtype<T>, "T is not a valid type for Event");
    return std::get<T>(m_data);
}

template<typename T>
void Event::reset()
{
    static_assert(is_event_subtype<T>, "T is not a valid type for Event");
    m_data = T{};
}