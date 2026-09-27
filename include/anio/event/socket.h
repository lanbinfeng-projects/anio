#ifndef ANIO_EVENT_SOCKET_H
#define ANIO_EVENT_SOCKET_H

#include <sys/socket.h>

#include <anio/event/channel.h>

namespace anio
{

namespace event
{

class socket : public channel {
public:
	socket();

	virtual ~socket();

	virtual void handle_read() override final;

	virtual void handle_accept(int, const struct sockaddr *, socklen_t) = 0;
};

} // namespace event

} // namespace anio

#endif // ANIO_EVENT_SOCKET_H
