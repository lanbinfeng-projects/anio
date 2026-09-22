#ifndef ANIO_NET_CONNECT_H
#define ANIO_NET_CONNECT_H

#include <functional>

#include <anio/buffer.h>
#include <anio/event/channel.h>
#include <anio/event/event_loop.h>
#include <anio/unique_fd.h>

namespace anio
{

namespace net
{

class connect : public event::channel {
public:
	using message_callback = std::function<void(connect *)>;

	connect(int fd, event::event_loop *loop);

	virtual const int &fd() const override final
	{
		return _fd.fd();
	}

	virtual void handle_read() override final;

	virtual void handle_write() override final;

	virtual void handle_error() override final;

	size_t recv(void *buf, size_t len)
	{
		size_t res = _read_buf.read(buf, len);
		_read_buf.commit_read(res);
		return res;
	}

	size_t send(const void *buf, size_t len)
	{
		size_t res = _write_buf.write(buf, len);
		enable_writable();
		_loop->add(this);
		return res;
	}

	void set_message_callback(const message_callback &callback)
	{
		_callback = callback;
	}

private:
	unique_fd _fd;

	event::event_loop *_loop;

	buffer _read_buf;
	buffer _write_buf;

	message_callback _callback;
};

} // namespace net

} // namespace anio

#endif // ANIO_NET_CONNECT_H
