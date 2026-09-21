#include <assert.h>
#include <string.h>

#include <anio/buffer.h>

#define TEXT "Hello world!"
#define LEN sizeof(TEXT)

int main(void)
{
	using namespace anio;

	buffer buf;
	char data[LEN];
	int res;

	res = buf.write(TEXT, LEN);
	assert(res == LEN);

	res = buf.read(data, LEN);
	assert(res == LEN);

	assert(strcmp(data, TEXT) == 0);

	return 0;
}