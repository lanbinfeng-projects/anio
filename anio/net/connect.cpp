#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <system_error>

#include <anio/log.h>
#include <anio/net/connect.h>

static constexpr size_t buf_size = 64 * 1024;

namespace anio
{

namespace net
{

connect::connect(int fd, event::event_loop *loop,
		 const message_callback &callback)
	: _fd(fd)
	, _loop(loop)
	, _callback(callback)
{
	log_trace("connect({}): init: fd={}.", static_cast<const void *>(this),
		  fd);

	enable_readable();
	loop->add(this);
}

connect::~connect()
{
	log_trace("connect({}): exit: fd={}.", static_cast<const void *>(this),
		  fd());
}

void connect::handle_error()
{
	using namespace std;

	int optval;
	socklen_t optlen = static_cast<socklen_t>(sizeof(int));
	int res;

	res = getsockopt(_fd.fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen);
	if (res < 0)
		log_error("connect({}): handle_error: getsockopt: {}.",
			  static_cast<const void *>(this), strerror(errno));
	else
		log_error("connect({}): handle_error: {}.",
			  static_cast<const void *>(this), strerror(optval));
	close();
}

void connect::handle_read()
{
	uint8_t buf[buf_size];
	ssize_t res;

	res = read(_fd.fd(), buf, buf_size);
	if (res < 0) {
		log_error("connect({}): read: {}.",
			  static_cast<const void *>(this), strerror(errno));
		close();
		return;
	}

	log_trace("connect({}): read: res={}.", static_cast<const void *>(this),
		  res);

	if (res == 0) {
		close();
		return;
	}

	_read_buf.write(buf, res);

	if (_callback)
		_callback(this);
}

void connect::handle_write()
{
	uint8_t buf[buf_size];
	size_t count;
	ssize_t res;

	count = _write_buf.read(buf, buf_size);
	if (count == 0) {
		disable_writable();
		_loop->mod(this);
		return;
	}

	res = write(_fd.fd(), buf, count);
	if (res < 0) {
		log_error("connect({}): write: {}.",
			  static_cast<const void *>(this), strerror(errno));
		return;
	}
	_write_buf.commit_read(res);

	log_trace("connect({}): write: res={}.",
		  static_cast<const void *>(this), res);
}

void connect::handle_happened()
{
	log_trace("connect({}): handle_happened.",
		  static_cast<const void *>(this));
	close();
}

void connect::close()
{
	log_trace("connect({}): close: event_loop({}): del.",
		  static_cast<const void *>(this),
		  static_cast<const void *>(_loop));
	_loop->del(this);

	log_trace("connect({}): close.", static_cast<const void *>(this));

	// 当连接在读事件或写事件时关闭，同时发生EPOLLHUP，则会访问过期地址。
	delete this;
}

} // namespace net

} // namespace anio
