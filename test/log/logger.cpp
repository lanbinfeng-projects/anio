#include <anio/log/logger.h>

int main(void)
{
	using namespace anio::log;

	logger log("test({})", nullptr);

	log.info("Hello world!");

	return 0;
}