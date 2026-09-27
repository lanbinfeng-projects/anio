#include <anio/log.h>

int main(void)
{
        using namespace anio;

        log_info("Hello {}!", "world");
        log_debug("Debug info.");

        return 0;
}