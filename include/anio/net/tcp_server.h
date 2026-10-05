#ifndef ANIO_NET_TCP_SERVER_H
#define ANIO_NET_TCP_SERVER_H

#include <memory>
#include <string>
#include <vector>

#include <anio/event/event_loop.h>
#include <anio/event/socket.h>
#include <anio/log/logger.h>
#include <anio/net/connect.h>

namespace anio
{

namespace net
{

class tcp_server {
public:
	tcp_server()
		: _logger("tcp_server({})", static_cast<const void *>(this))
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

	virtual void message_handle(connect *) = 0;

	event::event_loop *next_loop()
	{
		return &_loop;
	}

	void listen(std::string_view node, std::string_view service);

private:
	log::logger _logger;

	event::event_loop _loop;
	std::vector<std::unique_ptr<event::socket>> _sockets;
};

} // namespace net

} // namespace anio

#endif // ANIO_NET_TCP_SERVER_H
