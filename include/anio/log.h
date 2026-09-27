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

template <class... Args>
void log_println(log_level level, std::format_string<Args...> fmt,
		 Args &&...args)
{
	using namespace std;
	using namespace std::chrono;

	FILE *stream;
	// 通过毫秒存储系统时间
	auto sys_now = system_clock::now();
	// 转换为本地时间
	auto now = current_zone()->to_local(sys_now);

	if (level > log_get_level())
		return;

	switch (level) {
	case L_FATAL:
	case L_ERROR:
	case L_WARN:
		stream = stderr;
		break;

	case L_INFO:
	case L_DEBUG:
	case L_TRACE:
		stream = stdout;
		break;

	default:
		stream = nullptr;
	}

	println(stream, "{}: {}", now,
		format(fmt, std::forward<Args>(args)...));
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
