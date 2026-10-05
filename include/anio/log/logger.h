#ifndef ANIO_LOG_LOGGER_H
#define ANIO_LOG_LOGGER_H

#include <string>

namespace anio
{

namespace log
{

class logger {
public:
	logger() = default;

	logger(std::string_view name)
		: _name(name)
	{
	}

private:
	std::string _name;
};

} // namespace log

} // namespace anio

#endif // ANIO_LOG_LOGGER_H