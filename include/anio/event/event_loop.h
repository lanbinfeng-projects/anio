#ifndef ANIO_EVENT_LOOP_H
#define ANIO_EVENT_LOOP_H

#include <memory>

#include <anio/event/channel.h>

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

	void exit();

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace event

} // namespace anio

#endif // ANIO_EVENT_LOOP_H
