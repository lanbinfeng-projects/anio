#include <memory>

#include <anio/channel.h>

namespace anio
{

class channel::impl {
public:
	impl(int fd)
		: _fd(fd)
		, _readable(false)
		, _writable(false)
	{
	}

	const int &fd() const
	{
		return _fd;
	}

	void enable_readable()
	{
		_readable = true;
	}

	void disable_readable()
	{
		_readable = false;
	}

	bool readable() const
	{
		return _readable;
	}

	void enable_writable()
	{
		_writable = true;
	}

	void disable_writable()
	{
		_writable = false;
	}

	bool writable() const
	{
		return _writable;
	}

private:
	const int _fd;

	bool _readable;
	bool _writable;
};

channel::channel(int fd)
	: _pimpl(std::make_unique<impl>(fd))
{
}

channel::~channel() = default;

const int &channel::fd() const
{
	return _pimpl->fd();
}

void channel::enable_readable()
{
	_pimpl->enable_readable();
}

void channel::disable_readable()
{
	_pimpl->disable_readable();
}

bool channel::readable() const
{
	return _pimpl->readable();
}

void channel::enable_writable()
{
	_pimpl->enable_writable();
}

void channel::disable_writable()
{
	_pimpl->disable_writable();
}

bool channel::writable() const
{
	return _pimpl->writable();
}

} // namespace anio
