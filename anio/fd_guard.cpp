#include <errno.h>
#include <unistd.h>

#include <anio/fd_guard.h>

namespace anio
{

class fd_guard::impl {
public:
	impl(int fd)
		: _fd(fd)
		, _callback(nullptr)
	{
	}

	~impl()
	{
		int save_errno;
		int res;

		save_errno = errno;

		res = close(_fd);
		if (res < 0)
			if (_callback)
				_callback(_fd);

		errno = save_errno;
	}

	const int &fd() const
	{
		return _fd;
	}

	void set_close_error_callback(close_error_callback callback)
	{
		_callback = callback;
	}

private:
	const int _fd;
	close_error_callback _callback;
};

fd_guard::fd_guard(int fd)
	: _pimpl(std::make_unique<impl>(fd))
{
}

fd_guard::~fd_guard() = default;

const int &fd_guard::fd() const
{
	return _pimpl->fd();
}

void fd_guard::set_close_error_callback(close_error_callback callback)
{
	_pimpl->set_close_error_callback(callback);
}

} // namespace anio
