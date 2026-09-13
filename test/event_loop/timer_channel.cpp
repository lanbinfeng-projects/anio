#include <assert.h>
#include <stdint.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <anio/log.h>

#include "timer_channel.h"

static int _timerfd()
{
	int fd;
	struct itimerspec it;
	int res;

	fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	assert(fd >= 0);

	it.it_value.tv_sec = 0;
	it.it_value.tv_nsec = 300'000'000;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_nsec = 300'000'000;
	res = timerfd_settime(fd, 0, &it, nullptr);
	assert(res >= 0);

	return fd;
}

timer_channel::timer_channel(anio::event_loop *loop)
	: _fd(_timerfd())
	, _loop(loop)
{
	enable_readable();

	log_trace("timer_channel(%p): creates: fd=%d.\n", this, _fd.fd());
}

timer_channel::~timer_channel()
{
	using namespace anio;

	log_trace("timer_channel(%p): exit: fd=%d.\n", this, _fd.fd());
}

const int &timer_channel::fd() const
{
	return _fd.fd();
}

void timer_channel::handle_read()
{
	using namespace anio;

	static int count = 0;
	uint64_t buf;
	int res;

	res = read(fd(), &buf, sizeof(uint64_t));
	assert(res == sizeof(uint64_t));

	log_trace("timeout: buf=%llu.\n", buf);

	count += buf;
	if (count >= 3)
		_loop->exit();
}

void timer_channel::handle_write()
{
	using namespace anio;

	log_error("Function not implemented.\n");
}

void timer_channel::handle_error()
{
	using namespace anio;

	log_error("Function not implemented.\n");
}
