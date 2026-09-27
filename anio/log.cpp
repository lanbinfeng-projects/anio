#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <print>

#include <anio/log.h>

namespace anio
{

static log_level current_level = L_INFO;

void log_set_level(log_level level)
{
	current_level = level;
}

log_level log_get_level()
{
	return current_level;
}

void log_println_impl(log_level level, std::string_view s)
{
	using namespace std;
	using namespace std::chrono;

	FILE *stream;

	if (level > log_get_level())
		return;

	// 通过毫秒存储系统时间
	auto sys_now = system_clock::now();
	// 转换为本地时间
	auto now = current_zone()->to_local(sys_now);
	std::string_view str_level;

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

	if (level == L_FATAL)
		str_level = "FATAL";
	else if (level == L_ERROR)
		str_level = "ERROE";
	else if (level == L_WARN)
		str_level = "WARN";
	else if (level == L_INFO)
		str_level = "INFO";
	else if (level == L_DEBUG)
		str_level = "DEBUG";
	else if (level == L_TRACE)
		str_level = "TRACE";

	println(stream, "{} {:>5}: {}", now, str_level, s);

	if (level == L_FATAL)
		abort();
}

} // namespace anio
