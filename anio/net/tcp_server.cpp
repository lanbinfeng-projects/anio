#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>

#include <memory>
#include <system_error>

#include <anio/event/socket.h>
#include <anio/log/log.h>
#include <anio/net/connect.h>
#include <anio/net/tcp_server.h>
#include <anio/unique_fd.h>

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
		: _logger("soccket_impl({})", static_cast<const void *>(this))
		, _server(server)
		, _fd(_bind(ai))
	{
		using namespace anio::log;

		_logger.trace("init: fd={}, server={}.", _fd.fd(),
			      static_cast<const void *>(server));
	}

	virtual ~socket_impl() override
	{
		using namespace anio::log;

		_logger.trace("exit: fd={}.", _fd.fd());
	}

	virtual const int &fd() const override final
	{
		return _fd.fd();
	}

	virtual void handle_accept(int fd, const struct sockaddr *addr,
				   socklen_t addrlen) override final
	{
		using namespace std;
		using namespace anio::log;
		using namespace anio::net;

		_logger.trace("accept connect: fd={}.", fd);

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
	anio::log::logger _logger;

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

	_logger.info("listen: {}:{}", node, service);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = 0;
	errcode = getaddrinfo(node.data(), service.data(), &hints, &res);
	if (errcode)
		_logger.error("listen: {}.", gai_strerror(errcode));

	for (ai = res; ai != nullptr; ai = ai->ai_next) {
		unique_ptr<socket> p = make_socket(this, ai);
		_loop.add(p.get());
		_sockets.emplace_back(move(p));
	}
}

} // namespace net

} // namespace anio
