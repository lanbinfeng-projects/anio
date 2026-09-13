#ifndef ANIO_CHANNEL_H
#define ANIO_CHANNEL_H

#include <memory>

namespace anio
{

class channel {
public:
	channel(int fd);

	~channel();

	const int &fd() const;

	void enable_readable();

	void disable_readable();

	bool readable() const;

	void enable_writable();

	void disable_writable();

	bool writable() const;

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_CHANNEL_H
