#include <netdb.h>

#include <memory>

#include <anio/event/socket.h>
#include <anio/log.h>
#include <anio/net/tcp_server.h>

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
		log_error("tcp_server: listen: %s.\n", gai_strerror(errcode));

	for (ai = res; ai != nullptr; ai = ai->ai_next) {
		socket_ptr sock = make_unique<socket>(ai);
		_loop.add(sock.get());
		_sockets.emplace_back(move(sock));
	}
}

} // namespace net

} // namespace anio
