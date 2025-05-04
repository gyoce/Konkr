#ifndef ENGINE_TIME_MANAGER_HPP
#define ENGINE_TIME_MANAGER_HPP

#include <chrono>

class TimeManager
{
public:
    TimeManager();

    /// <summary>
    /// Get the delta time since the last frame.
    /// </summary>
    static float get_delta_time();

    using UP = std::unique_ptr<TimeManager>;

private:
    /// <summary>
    /// Internal method to start the frame i.e. save the current time.
    /// </summary>
    void start_frame();

    /// <summary>
    /// Internal method to end the frame i.e. calculate the delta time.
    /// </summary>
    void end_frame();

    float m_delta_time{};
    std::chrono::steady_clock::time_point m_start_time{};

    static TimeManager* s_instance;
    friend class Game;
};

#endif // ENGINE_TIME_MANAGER_HPP