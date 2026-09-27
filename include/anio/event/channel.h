#ifndef ANIO_EVENT_CHANNEL_H
#define ANIO_EVENT_CHANNEL_H

namespace anio
{

namespace event
{

class channel {
public:
	channel()
		: _readable(false)
		, _writable(false)
	{
	}

	virtual const int &fd() const = 0;

	virtual void handle_read();

	virtual void handle_write();

	virtual void handle_error();

	virtual void handle_happened();

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

} // namespace event

} // namespace anio

#endif // ANIO_EVENT_CHANNEL_H
