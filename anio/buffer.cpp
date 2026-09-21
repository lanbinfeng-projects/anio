#include <errno.h>
#include <stdlib.h>
#include <string.h>

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
	, _write_index(0)
	, _read_index(0)
{
}

buffer::~buffer()
{
	free(_data);
}

size_t buffer::write(const void *buf, size_t count)
{
	using namespace std;

	if (_capacity < (_write_index + count)) {
		size_t new_cap;
		void *p;

		for (new_cap = _capacity; new_cap < _write_index + count;
		     new_cap *= 2)
			;

		p = realloc(_data, new_cap);
		if (p == nullptr)
			throw system_error(errno, system_category());
		if (p != _data)
			_data = static_cast<uint8_t *>(p);
		_capacity = new_cap;
	}

	memcpy(_data + _write_index, buf, count);
	_write_index += count;

	return count;
}

size_t buffer::read(void *buf, size_t count)
{
	using namespace std;

	size_t ready = _write_index - _read_index;
	size_t res = ready < count ? ready : count;

	memcpy(buf, _data + _read_index, res);
	_read_index += res;

	// 缩容
	if (_read_index >= _capacity / 2) {
		void *p;

		memmove(_data, _data + _read_index, _write_index - _read_index);
		_write_index -= _read_index;
		_read_index = 0;

		p = realloc(_data, _capacity / 2);
		if (p == nullptr)
			throw system_error(errno, system_category());
		if (p != _data) {
			free(_data);
			_data = static_cast<uint8_t *>(p);
		}
		_capacity /= 2;
	}

	return res;
}

} // namespace anio
