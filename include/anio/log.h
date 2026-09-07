#ifndef ANIO_LOG_H
#define ANIO_LOG_H

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

void log_printf(log_level level, const char *format, ...);

template <class... Args>
void log_fatal(const char *format, Args... args)
{
	log_printf(L_FATAL, format, args...);
}

template <class... Args>
void log_error(const char *format, Args... args)
{
	log_printf(L_ERROR, format, args...);
}

template <class... Args>
void log_warn(const char *format, Args... args)
{
	log_printf(L_WARN, format, args...);
}

template <class... Args>
void log_info(const char *format, Args... args)
{
	log_printf(L_INFO, format, args...);
}

template <class... Args>
void log_debug(const char *format, Args... args)
{
	log_printf(L_DEBUG, format, args...);
}

template <class... Args>
void log_trace(const char *format, Args... args)
{
	log_printf(L_TRACE, format, args...);
}

} // namespace anio

#endif // ANIO_LOG_H
