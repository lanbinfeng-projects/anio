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

void connect::handle_read()
{
	uint8_t buf[buf_size];
	ssize_t res;

	res = read(_fd.fd(), buf, buf_size);
	if (res < 0)
		log_warn("connect: read: %s.\n", strerror(errno));
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
	} else {
		res = write(_fd.fd(), buf, count);
		if (res < 0)
			log_warn("connect: write: %s.\n", strerror(errno));
		_write_buf.commit_read(res);
	}
}

} // namespace net

} // namespace anio
