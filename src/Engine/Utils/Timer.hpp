#ifndef ENGINE_TIMER_HPP
#define ENGINE_TIMER_HPP

#include <functional>

class Timer
{
public:
    Timer() = default;
    Timer(float delay, std::function<void()> callback);

    void set_delay(const float delay) { m_delay = delay; }
    void set_callback(std::function<void()> callback) { m_callback = std::move(callback); }

    void update();

private:
    float m_delay{};
    std::function<void()> m_callback = nullptr;
    float m_time{};
};

#endif // ENGINE_TIMER_HPP