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
		anio::log_debug("close(fd=%d): failed: %s.\n", fd,
				strerror(errno));

	errno = save_errno;
}

namespace anio
{

class unique_fd::impl {
public:
	impl()
		: _fd(-1)
	{
	}

	impl(int fd)
		: _fd(fd)
	{
	}

	impl &operator=(int fd)
	{
		_fd = fd;
		return *this;
	}

	~impl()
	{
		if (_fd >= 0)
			_close(_fd);
	}

	const int &fd() const
	{
		return _fd;
	}

private:
	int _fd;
};

unique_fd::unique_fd()
	: _pimpl(std::make_unique<impl>())
{
}

unique_fd::unique_fd(int fd)
	: _pimpl(std::make_unique<impl>(fd))
{
}

unique_fd &unique_fd::operator=(int fd)
{
	*_pimpl = fd;
	return *this;
}

unique_fd::unique_fd(unique_fd &&) = default;

unique_fd &unique_fd::operator=(unique_fd &&) = default;

unique_fd::~unique_fd() = default;

const int &unique_fd::fd() const
{
	return _pimpl->fd();
}

} // namespace anio
