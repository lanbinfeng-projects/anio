#include <errno.h>
#include <sys/epoll.h>

#include <system_error>
#include <vector>

#include <anio/event/event_loop.h>
#include <anio/log/log.h>

template <class... Args>
static void _log_trace(const anio::event::event_loop *loop,
		       std::format_string<Args...> fmt, Args &&...args)
{
	using namespace anio::log;
	using namespace std;

	log_trace("event_loop({}): {}", static_cast<const void *>(loop),
		  format(fmt, forward<Args>(args)...));
}

static int _epoll_create()
{
	using namespace std;

	int fd;

	fd = epoll_create1(EPOLL_CLOEXEC);
	if (fd < 0)
		throw system_error(errno, system_category());

	return fd;
}

static void _handle_event(anio::event::event_loop *loop,
			  struct epoll_event *event)
{
	using namespace anio::event;

	channel *ch = static_cast<channel *>(event->data.ptr);
	uint32_t revents = event->events;

	if (revents & EPOLLERR)
		ch->handle_error();

	if (revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
		ch->handle_read();

	if (revents & EPOLLOUT)
		ch->handle_write();

	if (revents & EPOLLHUP)
		ch->handle_happened();
}

namespace anio
{

namespace event
{

event_loop::event_loop()
	: _epfd(_epoll_create())
	, _maxevents(0)
{
	_log_trace(this, "epoll_create(): epfd={}.", _epfd.fd());
}

event_loop::~event_loop()
{
	_log_trace(this, "exit: epfd={}.", _epfd.fd());
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
		event.events |= EPOLLIN | EPOLLPRI | EPOLLRDHUP;
	if (ch->writable())
		event.events |= EPOLLOUT;

	_log_trace(this,
		   "add: epoll_ctl("
		   "epfd = {}, EPOLL_CTL_ADD, fd = {}, "
		   "event = {{ events = {}, data = {} }}).",
		   _epfd.fd(), fd, static_cast<uint32_t>(event.events),
		   static_cast<const void *>(event.data.ptr));

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
		event.events |= EPOLLIN | EPOLLPRI | EPOLLRDHUP;
	if (ch->writable())
		event.events |= EPOLLOUT;

	_log_trace(this,
		   "mod: epoll_ctl("
		   "epfd = {}, EPOLL_CTL_MOD, fd = {}, "
		   "event = {{ events = {}, data = {} }}).",
		   _epfd.fd(), fd, static_cast<uint32_t>(event.events),
		   static_cast<const void *>(event.data.ptr));

	res = epoll_ctl(_epfd.fd(), EPOLL_CTL_MOD, fd, &event);
	if (res < 0)
		throw system_error(errno, system_category());
}

void event_loop::del(channel *ch)
{
	using namespace std;

	int fd = ch->fd();
	int res;

	_log_trace(this,
		   "del: epoll_ctl("
		   "epfd = {}, EPOLL_CTL_DEL, fd = {}).",
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
			_handle_event(this, &events[i]);
	}
}

} // namespace event

} // namespace anio
