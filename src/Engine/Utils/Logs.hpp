#ifndef ENGINE_LOGS_HPP
#define ENGINE_LOGS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <chrono>
#include <iomanip>

namespace logs
{
    namespace internal
    {
        struct LogContext
        {
            const char* m_format = nullptr;
            int m_format_size = 0;
            int m_index = 0;
            std::stringstream m_stream{};
        };

        inline std::string get_local_time_str()
        {
            const auto now = std::chrono::system_clock::now();
            time_t time = std::chrono::system_clock::to_time_t(now);
            std::tm tm{};
#if defined(_MSC_VER)
            localtime_s(&tm, &time);
#else
            tm = *std::localtime(&time);
#endif  
            std::stringstream ss{};
            ss << std::put_time(&tm, "%H:%M:%S");
            return ss.str();
        }

        template<typename T, class... Args>
        void format_log(LogContext& context, T&& current, Args&&... args)
        {
            while (context.m_index < context.m_format_size)
            {
                if (context.m_format[context.m_index] == '{' && context.m_format_size > context.m_index + 1 && context.m_format[context.m_index + 1] == '}')
                {
                    context.m_index = context.m_index + 2;
                    context.m_stream << std::forward<T>(current);
                    format_log(context, std::forward<Args>(args)...);
                }
                else
                {
                    context.m_stream << context.m_format[context.m_index];
                }
                context.m_index++;
            }
        }

        inline void format_log(LogContext& context)
        {
            while (context.m_index < context.m_format_size)
            {
                context.m_stream << context.m_format[context.m_index];
                context.m_index++;
            }
        }

        inline LogContext get_new_log_context(const char* format)
        {
            return LogContext
            {
                .m_format = format,
                .m_format_size = static_cast<int>(strlen(format))
            };
        }

        inline std::string green(const std::string& text)
        {
            return "\033[32m" + text + "\033[0m";
        }

        inline std::string bold_and_red(const std::string& text)
        {
            return "\033[1;31m" + text + "\033[0m";
        }
    } // namespace internal

    template <class... Args>
    void message(const char* format, Args&&... args)
    {
#ifndef NDEBUG
        internal::LogContext context = internal::get_new_log_context(format);
        context.m_stream << "LOG:   [" << internal::get_local_time_str() << "]: ";
        if constexpr (sizeof...(args) > 0)
            internal::format_log(context, std::forward<Args>(args)...);
        else
            internal::format_log(context);
        std::cout << internal::green(context.m_stream.str()) << "\n";
#else
        (void)format;
#endif
    }

    template <class... Args>
    void error(const char* format, Args&&... args)
    {
#ifndef NDEBUG
        internal::LogContext context = internal::get_new_log_context(format);
        context.m_stream << "ERROR:   [" << internal::get_local_time_str() << "]: ";
        if constexpr (sizeof...(args) > 0)
            internal::format_log(context, std::forward<Args>(args)...);
        else
            internal::format_log(context);
        std::cerr << internal::bold_and_red(context.m_stream.str()) << "\n";
#else
        (void)format;
#endif
    }
} // namespace logs

#endif // ENGINE_LOGS_HPP