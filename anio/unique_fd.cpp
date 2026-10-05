#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <memory>
#include <utility>

#include <anio/log.h>
#include <anio/unique_fd.h>

static void _close(int fd)
{
	int save_errno;
	int res;

	save_errno = errno;

	res = close(fd);
	if (res < 0)
		anio::log_debug("close(fd={}): failed: {}.", fd,
				strerror(errno));

	errno = save_errno;
}

namespace anio
{

unique_fd::~unique_fd()
{
	if (_fd >= 0)
		_close(_fd);
}

} // namespace anio
