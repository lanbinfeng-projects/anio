#include <errno.h>
#include <sys/epoll.h>

#include <system_error>
#include <vector>

#include <anio/event/event_loop.h>
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

static void _handle_event(struct epoll_event *event)
{
	using namespace anio::event;

	channel *ch = static_cast<channel *>(event->data.ptr);
	uint32_t revents = event->events;

	if (revents & EPOLLERR)
		ch->handle_error();

	if (revents & (EPOLLIN | EPOLLPRI))
		ch->handle_read();

	if (revents & EPOLLOUT)
		ch->handle_write();
}

namespace anio
{

namespace event
{

event_loop::event_loop()
	: _epfd(_epoll_create())
	, _maxevents(0)
{
	log_trace("event_loop: epoll_create(): epfd=%d.\n", _epfd.fd());
}

event_loop::~event_loop()
{
	log_trace("event_loop: exit: epfd=%d.\n", _epfd.fd());
}

void event_loop::add(channel *ch)
{
	using namespace std;

	int fd = ch->fd();
	struct epoll_event event;
	int res;

	event.data.ptr = ch;
	event.events = 0;
	if (ch->readable())
		event.events |= EPOLLIN | EPOLLPRI;
	if (ch->writable())
		event.events |= EPOLLOUT;

	log_trace("event_loop: add: epoll_ctl("
		  "epfd = %d, EPOLL_CTL_ADD, fd = %d, "
		  "event = { events = %u, data = %p }).\n",
		  _epfd.fd(), fd, (unsigned int)event.events, event.data.ptr);

	res = epoll_ctl(_epfd.fd(), EPOLL_CTL_ADD, fd, &event);
	if (res < 0)
		throw system_error(errno, system_category());

	_maxevents++;
}

void event_loop::mod(channel *ch)
{
	using namespace std;

	int fd = ch->fd();
	struct epoll_event event;
	int res;

	event.data.ptr = ch;
	event.events = 0;
	if (ch->readable())
		event.events |= EPOLLIN | EPOLLPRI;
	if (ch->writable())
		event.events |= EPOLLOUT;

	log_trace("event_loop: mod: epoll_ctl("
		  "epfd = %d, EPOLL_CTL_MOD, fd = %d, "
		  "event = { events = %u, data = %p }).\n",
		  _epfd.fd(), fd, (unsigned int)event.events, event.data.ptr);

	res = epoll_ctl(_epfd.fd(), EPOLL_CTL_MOD, fd, &event);
	if (res < 0)
		throw system_error(errno, system_category());
}

void event_loop::del(channel *ch)
{
	using namespace std;

	int fd = ch->fd();
	int res;

	log_trace("event_loop: del: epoll_ctl("
		  "epfd = %d, EPOLL_CTL_DEL, fd = %d).\n",
		  _epfd.fd(), fd);

	res = epoll_ctl(_epfd.fd(), EPOLL_CTL_DEL, fd, nullptr);
	if (res < 0)
		throw system_error(errno, system_category());

	_maxevents--;
}

void event_loop::start()
{
	using namespace std;

	_stop = false;

	// 无监听的事件时立即退出
	if (_maxevents == 0)
		_stop = true;

	while (!_stop) {
		vector<struct epoll_event> events(_maxevents);
		int res;
		int i;

		res = epoll_wait(_epfd.fd(), events.data(), _maxevents, -1);
		if (res < 0)
			throw system_error(errno, system_category());

		for (i = 0; i != res; i++)
			_handle_event(&events[i]);
	}
}

} // namespace event

} // namespace anio
