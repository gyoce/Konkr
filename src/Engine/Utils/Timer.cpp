#include "Engine/Utils/Timer.hpp"

#include "Engine/Managers/TimeManager.hpp"

Timer::Timer(const float delay, std::function<void()> callback)
    : m_delay(delay), m_callback(std::move(callback))
{
}

void Timer::update()
{
    m_time += TimeManager::get_delta_time();
    if (m_time >= m_delay)
    {
        m_time = 0.0f;
        if (m_callback)
            m_callback();
    }
}
