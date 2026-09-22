#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <anio/log.h>
#include <anio/net/connect.h>

static constexpr size_t buf_size = 64 * 1024;

namespace anio
{

namespace net
{

connect::connect(int fd, event::event_loop *loop)
	: _fd(fd)
	, _loop(loop)
{
	enable_readable();
}

void connect::handle_read()
{
	uint8_t buf[buf_size];
	ssize_t res;

	res = read(_fd.fd(), buf, buf_size);
	if (res < 0)
		log_warn("connect: read: %s.\n", strerror(errno));
	_read_buf.write(buf, res);
}

void connect::handle_write()
{
	uint8_t buf[buf_size];
	size_t count;
	ssize_t res;

	count = _write_buf.read(buf, buf_size);
	res = write(_fd.fd(), buf, count);
	if (res < 0)
		log_warn("connect: write: %s.\n", strerror(errno));
	if (res != count) // 未写入的数据会丢失
		log_error("connect: write: res != count.\n");
}

void connect::handle_error()
{
}

} // namespace net

} // namespace anio
