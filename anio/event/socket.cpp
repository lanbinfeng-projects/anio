#include <errno.h>
#include <sys/socket.h>

#include <system_error>

#include <anio/event/socket.h>

namespace anio
{

namespace event
{

socket::socket()
	: _logger("socket({})", static_cast<const void *>(this))
{
	_logger.trace("init.");

	enable_readable();
}

socket::~socket()
{
	using namespace log;

	_logger.trace("exit.");
}

void socket::handle_read()
{
	using namespace std;

	int fd;
	struct sockaddr_storage addr;
	socklen_t addrlen;

	fd = accept4(this->fd(), reinterpret_cast<struct sockaddr *>(&addr),
		     &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

	if (fd < 0)
		throw system_error(errno, system_category());

	handle_accept(fd, reinterpret_cast<const struct sockaddr *>(&addr),
		      addrlen);
}

} // namespace event

} // namespace anio
