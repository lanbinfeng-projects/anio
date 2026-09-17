#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>

#include <system_error>

#include <anio/log.h>
#include <anio/net/socket.h>

// 通过addrinfo的地址创建sockfd
static anio::unique_fd _bind(const struct addrinfo *ai)
{
	using namespace anio;
	using namespace std;

	unique_fd fd;
	int optval;
	int res;

	res = socket(ai->ai_family,
		     ai->ai_socktype | SOCK_NONBLOCK | SOCK_CLOEXEC,
		     ai->ai_protocol);
	if (res < 0)
		throw system_error(errno, system_category());
	fd = res;

	optval = 1;
	res = setsockopt(fd.fd(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
			 &optval, sizeof(int));

	res = bind(fd.fd(), ai->ai_addr, ai->ai_addrlen);
	if (res < 0)
		throw system_error(errno, system_category());

	res = listen(fd.fd(), SOMAXCONN);
	if (res < 0)
		throw system_error(errno, system_category());

	return fd;
}

namespace anio
{

namespace net
{

socket::socket(const struct addrinfo *ai)
	: _fd(_bind(ai))
{
	enable_readable();
}

void socket::handle_read()
{
}

// 用于accept的sockfd不应该可写，所以不应该监听也不应该出现可写事件。
// 这个函数不应该被调用
void socket::handle_write()
{
	// 发送一个调试警告
	log_debug("socket::handle_write(): writable event.\n");
	disable_writable();
}

void socket::handle_error()
{
}

} // namespace net

} // namespace anio
