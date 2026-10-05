#include <anio/event/channel.h>

namespace anio
{

namespace event
{
void channel::handle_read()
{
	_logger.debug("handle_read: unimplemented.");
}

void channel::handle_write()
{
	_logger.debug("handle_write: unimplemented.");
}

void channel::handle_error()
{
	_logger.debug("handle_error: unimplemented.");
}

void channel::handle_happened()
{
	_logger.debug("handle_happened: unimplemented.");
}

} // namespace event

} // namespace anio
