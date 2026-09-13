#ifndef ANIO_TEST_EVENT_LOOP_TIMER_CHANNEL_H
#define ANIO_TEST_EVENT_LOOP_TIMER_CHANNEL_H

#include <anio/channel.h>
#include <anio/fd_guard.h>

class timer_channel : public anio::channel {
public:
	timer_channel();

	~timer_channel();

	virtual const int &fd() const override final;

	virtual void handle_read() override final;

	virtual void handle_write() override final;

	virtual void handle_error() override final;

private:
	anio::fd_guard _fd;
};

#endif // TEST_EVENT_LOOP_TIMER_CHANNEL_H
