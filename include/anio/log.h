#ifndef ANIO_LOG_H
#define ANIO_LOG_H

#include <stdio.h>

#include <chrono>
#include <format>
#include <print>

namespace anio
{

enum class log_level {
	L_FATAL,
#define L_FATAL log_level::L_FATAL
	L_ERROR,
#define L_ERROR log_level::L_ERROR
	L_WARN,
#define L_WARN log_level::L_WARN
	L_INFO,
#define L_INFO log_level::L_INFO
	L_DEBUG,
#define L_DEBUG log_level::L_DEBUG
	L_TRACE
#define L_TRACE log_level::L_TRACE
};

void log_set_level(log_level level);

log_level log_get_level();

void log_println_impl(log_level level, std::string_view s);

template <class... Args>
void log_println(log_level level, std::format_string<Args...> fmt,
		 Args &&...args)
{
	log_println_impl(level, format(fmt, std::forward<Args>(args)...));
}

template <class... Args>
void log_fatal(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_FATAL, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void log_error(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_ERROR, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void log_warn(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_WARN, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void log_info(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_INFO, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void log_debug(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_DEBUG, fmt, std::forward<Args>(args)...);
}

template <class... Args>
void log_trace(std::format_string<Args...> fmt, Args &&...args)
{
	log_println(L_TRACE, fmt, std::forward<Args>(args)...);
}

} // namespace anio

#endif // ANIO_LOG_H
