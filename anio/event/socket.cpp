#include <errno.h>
#include <sys/socket.h>

#include <system_error>

#include <anio/event/socket.h>
#include <anio/log.h>

template <class... Args>
static void _log_debug(std::format_string<Args...> fmt, Args &&...args)
{
	using namespace anio;
	using namespace std;

	log_debug("socket: {}", format(fmt, forward<Args>(args)...));
}

namespace anio
{

namespace event
{

socket::socket()
{
	log_trace("socket({}): init.", static_cast<const void *>(this));

	enable_readable();
}

socket::~socket()
{
	log_trace("socket({}): exit.", static_cast<const void *>(this));
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

// 用于accept的sockfd不应该可写，所以不应该监听也不应该出现可写事件。
// 这个函数不应该被调用
void socket::handle_write()
{
	// 发送一个调试警告
	_log_debug("handle_write(): writable event.");
	disable_writable();
}

} // namespace event

} // namespace anio
