#include <assert.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <condition_variable>
#include <mutex>
#include <thread>

#include <anio/log.h>
#include <anio/net/tcp_server.h>

std::mutex m;
std::condition_variable cv;
bool ready = false;

static void _ready()
{
	std::lock_guard lock(m);
	ready = true;
}

class server : anio::net::tcp_server {
public:
	server()
	{
		listen("localhost", "8080");
		_ready();
		cv.notify_one();
		start();
	}

	void message_handle(anio::net::connect *conn)
	{
		constexpr size_t size = 0xFF;

		char buf[size];
		size_t res;

		res = conn->recv(buf, size);
		if (strcmp(buf, "exit") == 0)
			exit();
		conn->send(buf, res);
	}
};

int main(void)
{
	using namespace anio;
	using namespace std;

	log_set_level(L_TRACE);

	jthread t([] { server s; });

	unique_lock lock(m);

	int fd;
	struct sockaddr_in addr;
	int res;

	constexpr size_t size = 0xFF;
	char buf[size];

	const char *msg = "Hello world!";
	const char *exit_msg = "exit";

	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(fd >= 0);

	cv.wait(lock, [] { return ready; });

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_port = htons(8080);
	res = connect(fd, reinterpret_cast<const struct sockaddr *>(&addr),
		      sizeof(struct sockaddr_in));
	assert(res == 0);

	strncpy(buf, msg, size);
	write(fd, buf, strlen(msg) + 1);
	read(fd, buf, size);
	assert(strcmp(buf, msg) == 0);

	write(fd, exit_msg, strlen(exit_msg) + 1);

	return 0;
}