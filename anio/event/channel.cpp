#include <anio/event/channel.h>
#include <anio/log.h>

namespace anio
{

namespace event
{

void channel::handle_happened()
{
	log_debug("channel({}): handle_happened: unimplemented.",
		  static_cast<const void *>(this));
}

} // namespace event

} // namespace anio
