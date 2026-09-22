#include <assert.h>
#include <string.h>

#include <anio/buffer.h>

#define TEXT1 "TEXT1"
#define TEXT2 "TEXT2"

int main(void)
{
	using namespace anio;

	buffer buf;
	char data[strlen(TEXT1) + strlen(TEXT2) + 1];
	int res;

	res = buf.read(data, 1024);
	assert(res == 0);

	res = buf.write(TEXT1, strlen(TEXT1));
	assert(res == strlen(TEXT1));

	res = buf.write(TEXT2, strlen(TEXT2));
	assert(res == strlen(TEXT2));

	res = buf.read(data, strlen(TEXT1));
	assert(res == strlen(TEXT1));
	buf.commit_read(res);

	res = buf.read(data + strlen(TEXT1), strlen(TEXT2));
	assert(res == strlen(TEXT2));
	buf.commit_read(res);

	data[strlen(TEXT1) + strlen(TEXT2)] = '\0';
	assert(strcmp(data, TEXT1 TEXT2) == 0);

	return 0;
}