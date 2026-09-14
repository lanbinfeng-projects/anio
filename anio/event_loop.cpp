#include <errno.h>
#include <sys/epoll.h>

#include <system_error>
#include <vector>

#include <anio/event_loop.h>
#include <anio/log.h>
#include <anio/unique_fd.h>

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
	using namespace anio;

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

class event_loop::impl {
public:
	impl()
		: _epfd(_epoll_create())
		, _maxevents(0)
	{
		log_trace("event_loop: epoll_create(): epfd=%d.\n", _epfd.fd());
	}

	~impl()
	{
		log_trace("event_loop: exit: epfd=%d.\n", _epfd.fd());
	}

	void add(channel *ch)
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
			  _epfd.fd(), fd, (unsigned int)event.events,
			  event.data.ptr);

		res = epoll_ctl(_epfd.fd(), EPOLL_CTL_ADD, fd, &event);
		if (res < 0)
			throw system_error(errno, system_category());

		_maxevents++;
	}

	void mod(channel *ch)
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
			  _epfd.fd(), fd, (unsigned int)event.events,
			  event.data.ptr);

		res = epoll_ctl(_epfd.fd(), EPOLL_CTL_MOD, fd, &event);
		if (res < 0)
			throw system_error(errno, system_category());
	}

	void del(channel *ch)
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

	void start()
	{
		using namespace std;

		if (_maxevents == 0)
			return;

		_stop = false;
		while (!_stop) {
			vector<struct epoll_event> events(_maxevents);
			int res;
			int i;

			res = epoll_wait(_epfd.fd(), events.data(), _maxevents,
					 -1);
			if (res < 0)
				throw system_error(errno, system_category());

			for (i = 0; i != res; i++)
				_handle_event(&events[i]);
		}
	}

	void exit()
	{
		_stop = true;
	}

private:
	unique_fd _epfd;

	bool _stop;
	int _maxevents;
};

event_loop::event_loop()
	: _pimpl(std::make_unique<impl>())
{
}

event_loop::~event_loop() = default;

void event_loop::add(channel *ch)
{
	_pimpl->add(ch);
}

void event_loop::mod(channel *ch)
{
	_pimpl->mod(ch);
}

void event_loop::del(channel *ch)
{
	_pimpl->del(ch);
}

void event_loop::start()
{
	_pimpl->start();
}

void event_loop::exit()
{
	_pimpl->exit();
}

} // namespace anio
