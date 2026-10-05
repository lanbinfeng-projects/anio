#include <anio/event/channel.h>
#include <anio/log/log.h>

namespace anio
{

namespace event
{
void channel::handle_read()
{
	using namespace log;

	log_debug("channel({}): handle_read: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_write()
{
	using namespace log;

	log_debug("channel({}): handle_write: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_error()
{
	using namespace log;

	log_debug("channel({}): handle_error: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_happened()
{
	using namespace log;

	log_debug("channel({}): handle_happened: unimplemented.",
		  static_cast<const void *>(this));
}

} // namespace event

} // namespace anio
