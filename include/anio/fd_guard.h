#ifndef ANIO_FD_GUARD_H
#define ANIO_FD_GUARD_H

#include <memory>

namespace anio
{

class fd_guard {
public:
	using close_error_callback = void (*)(int fd);

	fd_guard(int fd);

	fd_guard(fd_guard &&) = default;

	~fd_guard();

	const int &fd() const;

	void set_close_error_callback(close_error_callback callback);

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_FD_GUARD_H
