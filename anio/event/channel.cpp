#include <memory>

#include <anio/event/channel.h>

namespace anio
{

namespace event
{

class channel::impl {
public:
	impl()
		: _readable(false)
		, _writable(false)
	{
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
	bool _readable;
	bool _writable;
};

channel::channel()
	: _pimpl(std::make_unique<impl>())
{
}

channel::~channel() = default;

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

} // namespace event

} // namespace anio
