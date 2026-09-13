#ifndef ANIO_EVENT_LOOP_H
#define ANIO_EVENT_LOOP_H

#include <memory>

#include <anio/channel.h>

namespace anio
{

class event_loop {
public:
	event_loop();

	~event_loop();

	void add(channel *ch);

	void mod(channel *ch);

	void del(channel *ch);

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_EVENT_LOOP_H
