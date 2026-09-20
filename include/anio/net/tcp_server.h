#ifndef ANIO_NET_TCP_SERVER_H
#define ANIO_NET_TCP_SERVER_H

#include <memory>
#include <string>
#include <vector>

#include <anio/event/event_loop.h>

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
	event::event_loop _loop;
	std::vector<std::unique_ptr<event::socket>> _sockets;
};

} // namespace net

} // namespace anio

#endif // ANIO_NET_TCP_SERVER_H
