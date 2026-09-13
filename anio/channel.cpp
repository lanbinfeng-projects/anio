#include <memory>

#include <anio/channel.h>

namespace anio
{

class channel::impl {
public:
	impl(int fd)
		: _fd(fd)
	{
	}

	const int &fd() const
	{
		return _fd;
	}

private:
	const int _fd;
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

} // namespace anio
