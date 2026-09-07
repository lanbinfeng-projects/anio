#include <anio/log.h>

int main(void)
{
        using namespace anio;

        log_info("Hello %s!\n", "world");

        return 0;
}