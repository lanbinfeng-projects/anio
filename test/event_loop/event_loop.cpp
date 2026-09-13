#include <anio/event_loop.h>
#include <anio/log.h>

int main(void)
{
	using namespace anio;

	log_set_level(L_TRACE);

	event_loop loop;

	return 0;
}