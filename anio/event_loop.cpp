#include <sys/epoll.h>

#include <system_error>

#include <anio/event_loop.h>
#include <anio/fd_guard.h>
#include <anio/log.h>

static int _epoll_create()
{
	using namespace std;

	int fd;

	fd = epoll_create1(EPOLL_CLOEXEC);
	if (fd < 0)
		throw system_error(errno, system_category());

	return fd;
}

namespace anio
{

class event_loop::impl {
public:
	impl()
		: _fd(_epoll_create())
	{
		log_trace("event_loop: epoll_create(): fd=%d.\n", _fd.fd());
	}

	~impl()
	{
		log_trace("event_loop: close(fd=%d).\n", _fd.fd());
	}

private:
	fd_guard _fd;
};

event_loop::event_loop()
	: _pimpl(std::make_unique<impl>())
{
}

event_loop::~event_loop() = default;

} // namespace anio
