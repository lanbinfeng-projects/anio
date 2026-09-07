#include <stdarg.h>
#include <stdio.h>

#include <anio/log.h>

namespace anio
{

static log_level current_level = L_INFO;

void log_set_level(log_level level)
{
	current_level = level;
}

void log_printf(log_level level, const char *format, ...)
{
	FILE *stream;
	va_list ap;

	if (level > current_level)
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

	va_start(ap, format);
	vfprintf(stream, format, ap);
	va_end(ap);
}

} // namespace anio
