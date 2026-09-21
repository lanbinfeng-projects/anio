#ifndef ANIO_BUFFER_H
#define ANIO_BUFFER_H

#include <stddef.h>
#include <stdint.h>

namespace anio
{

class buffer {
public:
	buffer();

	~buffer();

	size_t write(const void *buf, size_t count);

	size_t read(void *buf, size_t count);

private:
	uint8_t *_data;
	size_t _capacity;
	size_t _write_index;
	size_t _read_index;
};

} // namespace anio

#endif // ANIO_BUFFER_H
