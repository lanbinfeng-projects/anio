#ifndef ANIO_UNIQUE_FD_H
#define ANIO_UNIQUE_FD_H

namespace anio
{

class unique_fd {
public:
	using close_error_callback = void (*)(int);

	unique_fd()
		: _fd(-1)
	{
	}

	unique_fd(int fd)
		: _fd(fd)
	{
	}

	unique_fd &operator=(int fd)
	{
		_fd = fd;
		return *this;
	}

	unique_fd(unique_fd &&r)
	{
		_fd = r._fd;
		r._fd = -1;
	}

	unique_fd &operator=(unique_fd &&r)
	{
		_fd = r._fd;
		r._fd = -1;

		return *this;
	}

	~unique_fd();

	const int &fd() const
	{
		return _fd;
	}

private:
	int _fd;
};

} // namespace anio

#endif // ANIO_UNIQUE_FD_H
