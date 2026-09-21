#include <anio/net/connect.h>

namespace anio
{

namespace net
{

connect::connect(int fd)
	: _fd(fd)
{
	enable_readable();
}

void connect::handle_read()
{
}

void connect::handle_write()
{
}

void connect::handle_error()
{
}

} // namespace net

} // namespace anio
