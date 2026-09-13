#include <anio/event_loop.h>
#include <anio/log.h>

#include "timer_channel.h"

int main(void)
{
	using namespace anio;

	log_set_level(L_TRACE);

	event_loop loop;
	timer_channel ch;

	loop.add(&ch);
	loop.mod(&ch);
	loop.del(&ch);

	return 0;
}