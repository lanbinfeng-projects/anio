#ifndef ANIO_EVENT_LOOP_H
#define ANIO_EVENT_LOOP_H

#include <memory>

namespace anio
{

class event_loop {
public:
	event_loop();

	~event_loop();

private:
	class impl;
	std::unique_ptr<impl> _pimpl;
};

} // namespace anio

#endif // ANIO_EVENT_LOOP_H
