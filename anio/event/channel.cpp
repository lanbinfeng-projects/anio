#include <anio/event/channel.h>
#include <anio/log.h>

namespace anio
{

namespace event
{
void channel::handle_read()
{
	log_debug("channel({}): handle_read: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_write()
{
	log_debug("channel({}): handle_write: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_error()
{
	log_debug("channel({}): handle_error: unimplemented.",
		  static_cast<const void *>(this));
}

void channel::handle_happened()
{
	log_debug("channel({}): handle_happened: unimplemented.",
		  static_cast<const void *>(this));
}

} // namespace event

} // namespace anio
