#include <errno.h>
#include <stdlib.h>

#include <system_error>

#include <anio/buffer.h>

#ifndef INIT_BUFFER_SIZE
#define INIT_BUFFER_SIZE ((size_t)(4 * 1024))
#endif

static uint8_t *_malloc(size_t size)
{
	using namespace std;

	void *p = malloc(size);
	if (p == nullptr)
		throw system_error(errno, system_category());

	return static_cast<uint8_t *>(p);
}

namespace anio
{

buffer::buffer()
	: _data(_malloc(INIT_BUFFER_SIZE))
	, _capacity(INIT_BUFFER_SIZE)
	, _read_index(0)
	, _write_index(0)
{
}

buffer::~buffer()
{
	free(_data);
}

} // namespace anio
