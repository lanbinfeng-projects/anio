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

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_CHANNEL_H
