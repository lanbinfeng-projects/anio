#ifndef ANIO_NET_TCP_SERVER_H
#define ANIO_NET_TCP_SERVER_H

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

private:
	event_loop _loop;
};

} // namespace net

} // namespace anio

#endif // ANIO_NET_TCP_SERVER_H
