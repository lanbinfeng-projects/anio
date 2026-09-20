#ifndef ANIO_EVENT_SOCKET_H
#define ANIO_EVENT_SOCKET_H

#include <netdb.h>

#include <anio/event/channel.h>
#include <anio/unique_fd.h>

namespace anio
{

namespace event
{

class socket : public channel {
public:
	socket(const struct addrinfo *ai);

	virtual const int &fd() const override final
	{
		return _fd.fd();
	}

	virtual void handle_read() override final;

	virtual void handle_write() override final;

	virtual void handle_error() override final;

private:
	unique_fd _fd;
};

} // namespace event

} // namespace anio

#endif // ANIO_EVENT_SOCKET_H
