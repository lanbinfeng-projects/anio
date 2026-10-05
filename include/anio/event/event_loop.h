#ifndef ANIO_EVENT_EVENT_LOOP_H
#define ANIO_EVENT_EVENT_LOOP_H

#include <anio/event/channel.h>
#include <anio/log/logger.h>
#include <anio/unique_fd.h>

namespace anio
{

namespace event
{

class event_loop {
public:
	event_loop();

	~event_loop();

	void add(channel *ch);

	void mod(channel *ch);

	void del(channel *ch);

	void start();

	void exit()
	{
		_stop = true;
	}

private:
	log::logger _logger;

	unique_fd _epfd;

	bool _stop;
	int _maxevents;
};

} // namespace event

} // namespace anio

#endif // ANIO_EVENT_EVENT_LOOP_H
