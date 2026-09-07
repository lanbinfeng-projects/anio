#include <anio/log.h>

int main(void)
{
        using namespace anio;

        log_info("Hello %s!\n", "world");
        log_debug("Debug info\n");

        return 0;
}