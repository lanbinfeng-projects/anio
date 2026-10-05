#include <anio/log/log.h>

int main(void)
{
	using namespace anio::log;

	log_info("Hello {}!", "world");
	log_debug("Debug info.");

	return 0;
}