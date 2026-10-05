#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <system_error>

#include <anio/net/connect.h>

static constexpr size_t buf_size = 64 * 1024;

namespace anio
{

namespace net
{

connect::connect(int fd, event::event_loop *loop,
		 const message_callback &callback)
	: _logger("connect({})", static_cast<const void *>(this))
	, _fd(fd)
	, _loop(loop)
	, _callback(callback)
{
	using namespace log;

	_logger.trace("init: fd={}.", fd);

	enable_readable();
	loop->add(this);
}

connect::~connect()
{
	using namespace log;

	_logger.trace("exit: fd={}.", fd());
}

void connect::handle_error()
{
	using namespace log;
	using namespace std;

	int optval;
	socklen_t optlen = static_cast<socklen_t>(sizeof(int));
	int res;

	res = getsockopt(_fd.fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen);
	if (res < 0)
		_logger.error("handle_error: getsockopt: {}.", strerror(errno));
	else
		_logger.error("handle_error: {}.", strerror(optval));
	close();
}

void connect::handle_read()
{
	using namespace log;

	uint8_t buf[buf_size];
	ssize_t res;

	res = read(_fd.fd(), buf, buf_size);
	if (res < 0) {
		_logger.error("read: {}.", strerror(errno));
		close();
		return;
	}

	_logger.trace("read: res={}.", res);

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
	using namespace log;

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
		_logger.error("write: {}.", strerror(errno));
		return;
	}
	_write_buf.commit_read(res);

	_logger.trace("write: res={}.", res);
}

void connect::handle_happened()
{
	using namespace log;

	_logger.trace("handle_happened.");
	close();
}

void connect::close()
{
	using namespace log;

	_logger.trace("close: event_loop({}): del.",
		      static_cast<const void *>(_loop));
	_loop->del(this);

	_logger.trace("close.");

	// 当连接在读事件或写事件时关闭，同时发生EPOLLHUP，则会访问过期地址。
	delete this;
}

} // namespace net

} // namespace anio
