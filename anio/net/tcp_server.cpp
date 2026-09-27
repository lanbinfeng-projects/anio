#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>

#include <memory>
#include <system_error>

#include <anio/event/socket.h>
#include <anio/log.h>
#include <anio/net/connect.h>
#include <anio/net/tcp_server.h>
#include <anio/unique_fd.h>

template <class... Args>
static void _log_error(std::format_string<Args...> fmt, Args &&...args)
{
	using namespace anio;
	using namespace std;

	log_error("tcp_server: {}", format(fmt, forward<Args>(args)...));
}

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
	if (res < 0)
		throw system_error(errno, system_category());

	res = bind(fd.fd(), ai->ai_addr, ai->ai_addrlen);
	if (res < 0)
		throw system_error(errno, system_category());

	res = listen(fd.fd(), SOMAXCONN);
	if (res < 0)
		throw system_error(errno, system_category());

	return fd;
}

class socket_impl : public anio::event::socket {
public:
	socket_impl(anio::net::tcp_server *server, const struct addrinfo *ai)
		: _server(server)
		, _fd(_bind(ai))
	{
	}

	virtual const int &fd() const override final
	{
		return _fd.fd();
	}

	virtual void handle_accept(int fd, const struct sockaddr *addr,
				   socklen_t addrlen) override final
	{
		using namespace std;
		using namespace anio::net;

		auto callback = [this](class connect *conn) {
			_server->message_handle(conn);
		};
		class connect *conn =
			new class connect(fd, _server->next_loop(), callback);
	}

	virtual void handle_error() override final
	{
	}

private:
	anio::net::tcp_server *_server;

	anio::unique_fd _fd;
};

static std::unique_ptr<anio::event::socket>
make_socket(anio::net::tcp_server *server, const struct addrinfo *ai)
{
	return std::make_unique<socket_impl>(server, ai);
}

namespace anio
{
namespace net
{

void tcp_server::listen(std::string_view node, std::string_view service)
{
	using namespace std;
	using namespace event;

	struct addrinfo hints;
	struct addrinfo *res;
	const struct addrinfo *ai;
	int errcode;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = 0;
	errcode = getaddrinfo(node.data(), service.data(), &hints, &res);
	if (errcode)
		_log_error("listen: {}.", gai_strerror(errcode));

	for (ai = res; ai != nullptr; ai = ai->ai_next) {
		unique_ptr<socket> p = make_socket(this, ai);
		_loop.add(p.get());
		_sockets.emplace_back(move(p));
	}
}

} // namespace net

} // namespace anio
