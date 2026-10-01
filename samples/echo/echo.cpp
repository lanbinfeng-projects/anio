#include <anio/log.h>
#include <anio/net/tcp_server.h>

class echo_server : private anio::net::tcp_server {
public:
	echo_server()
	{
		listen("0.0.0.0", "8080");
		start();
	}

	virtual void message_handle(anio::net::connect *conn) override final
	{
		constexpr size_t count = 0xFFFF;
		char buf[count];
		int res;

		while (res = conn->recv(buf, count))
			conn->send(buf, res);
	}
};

int main(void)
{
	using namespace anio;

	log_set_level(L_TRACE);

	echo_server s;

	return 0;
}