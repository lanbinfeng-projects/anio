#ifndef ANIO_NET_TCP_SERVER_H
#define ANIO_NET_TCP_SERVER_H

#include <memory>
#include <string>
#include <vector>

#include <anio/event_loop.h>

namespace anio
{

namespace net
{

class tcp_server {
public:
	tcp_server()
	{
	}

	void start()
	{
		_loop.start();
	}

	void exit()
	{
		_loop.exit();
	}

	void listen(std::string_view node, std::string_view service);

private:
	using socket_ptr = std::unique_ptr<socket>;

	event_loop _loop;
	std::vector<socket_ptr> _sockets;
};

} // namespace net

} // namespace anio

#endif // ANIO_NET_TCP_SERVER_H
