#ifndef ENGINE_RANDOM_HPP
#define ENGINE_RANDOM_HPP

#include <random>
#include <type_traits>

namespace engine_random
{
    namespace internal
    {
        inline std::mt19937 random_engine(std::random_device{}());
    }

    template<typename T> requires(std::is_integral_v<T>) T next(T min, T max)
    {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(internal::random_engine);
    }

    template<typename T> requires(std::is_floating_point_v<T>) T next(T min, T max)
    {
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(internal::random_engine);
    }
} // namespace engine_random

#endif // ENGINE_RANDOM_HPP