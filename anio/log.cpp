#include <stdarg.h>
#include <stdio.h>

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

	println(stream, "{}: {}", now, s);
}

} // namespace anio
