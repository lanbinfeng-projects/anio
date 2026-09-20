#ifndef ANIO_TEST_EVENT_LOOP_TIMER_CHANNEL_H
#define ANIO_TEST_EVENT_LOOP_TIMER_CHANNEL_H

#include <anio/event/channel.h>
#include <anio/event/event_loop.h>
#include <anio/unique_fd.h>

class timer_channel : public anio::event::channel {
public:
	timer_channel(anio::event::event_loop *loop);

	~timer_channel();

	virtual const int &fd() const override final;

	// 超时三次时退出
	virtual void handle_read() override final;

	virtual void handle_write() override final;

	virtual void handle_error() override final;

private:
	anio::unique_fd _fd;
	// 用于handle_read()
	anio::event::event_loop *_loop;
};

#endif // TEST_EVENT_LOOP_TIMER_CHANNEL_H
