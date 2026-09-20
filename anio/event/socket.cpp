#include <errno.h>
#include <sys/socket.h>

#include <system_error>

#include <anio/event/socket.h>
#include <anio/log.h>

namespace anio
{

namespace event
{

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
	log_debug("socket::handle_write(): writable event.\n");
	disable_writable();
}

} // namespace event

} // namespace anio
