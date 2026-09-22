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

	// 返回读取的字节
	// 考虑到数据被读取后不一定能当即处理，因此read不移动指针。
	// 当数据处理完成后，调用commit_read将指针移动，进行下一步操作。
	size_t read(void *buf, size_t count);

	// 移动读指针。
	// count应该小于read返回的数据，否则行为未定义。
	void commit_read(size_t count);

private:
	uint8_t *_data;
	size_t _capacity;
	size_t _write_index;
	size_t _read_index;
};

} // namespace anio

#endif // ANIO_BUFFER_H
