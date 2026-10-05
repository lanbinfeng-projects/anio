#ifndef ANIO_LOG_LOGGER_H
#define ANIO_LOG_LOGGER_H

#include <format>
#include <string>

#include <anio/log/log.h>

namespace anio
{

namespace log
{

class logger {
public:
	template <class... Args>
	logger(std::format_string<Args...> fmt, Args &&...args)
		: _prefix(std::format(fmt, std::forward<Args>(args)...) + ": ")
	{
	}

	template <class... Args>
	void fatal(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_fatal("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

	template <class... Args>
	void error(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_error("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

	template <class... Args>
	void warn(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_warn("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

	template <class... Args>
	void info(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_info("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

	template <class... Args>
	void debug(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_debug("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

	template <class... Args>
	void trace(std::format_string<Args...> fmt, Args &&...args)
	{
		using namespace std;

		log_trace("{}{}", _prefix, format(fmt, forward<Args>(args)...));
	}

private:
	std::string _prefix;
};

} // namespace log

} // namespace anio

#endif // ANIO_LOG_LOGGER_H