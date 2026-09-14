#ifndef ANIO_UNIQUE_FD_H
#define ANIO_UNIQUE_FD_H

#include <memory>

namespace anio
{

class unique_fd {
public:
	using close_error_callback = void (*)(int);

	unique_fd();

	unique_fd(int fd);

	unique_fd &operator=(int fd);

	unique_fd(unique_fd &&);

	unique_fd &operator=(unique_fd &&);

	~unique_fd();

	const int &fd() const;

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_UNIQUE_FD_H
