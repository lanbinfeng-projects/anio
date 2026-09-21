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

private:
	uint8_t *_data;
	size_t _capacity;
	size_t _read_index;
	size_t _write_index;
};

} // namespace anio

#endif // ANIO_BUFFER_H
