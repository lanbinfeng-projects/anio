#include <assert.h>
#include <stdint.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <utility>

#include <anio/log.h>
#include <anio/unique_fd.h>

static int _eventfd()
{
	int fd;

	fd = eventfd(0, EFD_CLOEXEC);
	assert(fd >= 0);

	return fd;
}

int main(void)
{
	using namespace anio;

	log_set_level(L_TRACE);

	unique_fd fd;
	uint64_t buf;
	int res;

	fd = _eventfd();

	buf = 1024;
	res = write(fd.fd(), &buf, sizeof(uint64_t));
	assert(res >= 0);
	assert(res == 8);

	res = read(fd.fd(), &buf, sizeof(uint64_t));
	assert(res >= 0);
	assert(res == 8);
	assert(buf == 1024);

	unique_fd mv_fd = std::move(fd);

	buf = 1024;
	res = write(mv_fd.fd(), &buf, sizeof(uint64_t));
	assert(res >= 0);
	assert(res == 8);

	res = read(mv_fd.fd(), &buf, sizeof(uint64_t));
	assert(res >= 0);
	assert(res == 8);
	assert(buf == 1024);

	return 0;
}