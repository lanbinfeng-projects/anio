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

log_level log_get_level()
{
	return current_level;
}

} // namespace anio
