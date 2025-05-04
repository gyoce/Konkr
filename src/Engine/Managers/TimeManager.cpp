#include "Engine/Managers/TimeManager.hpp"

#include "Engine/Utils/Logs.hpp"

TimeManager* TimeManager::s_instance = nullptr;

TimeManager::TimeManager()
{
    if (s_instance != nullptr)
    {
        logs::error("Only one TimeManager can exist.");
        throw std::runtime_error("TimeManager already exists");
    }
    s_instance = this;
}

void TimeManager::start_frame()
{
    m_start_time = std::chrono::steady_clock::now();
}

void TimeManager::end_frame()
{
    const std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    m_delta_time = std::chrono::duration<float>(current_time - m_start_time).count();
}

float TimeManager::get_delta_time()
{
    return s_instance->m_delta_time;
}
