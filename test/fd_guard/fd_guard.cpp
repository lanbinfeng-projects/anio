#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <anio/fd_guard.h>
#include <anio/log.h>

#define N 1024

static void error(int fd)
{
	using namespace anio;
	using namespace std;

	assert(0);
}

static anio::fd_guard _eventfd()
{
	int fd;


	fd = eventfd(0, EFD_CLOEXEC);
	assert(fd >= 0);

	return fd;
}

int main(void)
{
	using namespace std;
	using namespace anio;

	log_set_level(L_DEBUG);

	fd_guard fd = _eventfd();

	constexpr size_t count = sizeof(uint64_t);
	uint64_t buf;

	int res;

	buf = N;
	res = write(fd.fd(), &buf, count);
	assert(res == count);

	res = read(fd.fd(), &buf, count);
	assert(res == count);

	assert(buf == N);

	return 0;
}