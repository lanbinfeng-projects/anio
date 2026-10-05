#include <anio/log/log.h>

int main(void)
{
	using namespace anio::log;

	log_fatal("fatal.");

	return 0;
}