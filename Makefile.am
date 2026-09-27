AUTOMAKE_OPTIONS	= foreign subdir-objects

ACLOCAL_AMFLAGS	= -I m4

EXTRA_DIST	= autogen.sh

#
# flags
#
AM_CPPFLAGS	= -Iinclude
AM_CXXFLAGS	= -std=c++23
LDADD		= ./libanio.la

#
# headers
#
include_aniodir	= $(includedir)/anio
include_anio_eventdir	= $(include_aniodir)/event
include_anio_netdir	= $(include_aniodir)/net

include_anio_HEADERS	= include/anio/buffer.h \
			  include/anio/log.h \
			  include/anio/unique_fd.h

include_anio_event_HEADERS	= include/anio/event/channel.h \
				  include/anio/event/event_loop.h \
				  include/anio/event/socket.h

include_anio_net_HEADERS	= include/anio/net/connect.h \
				  include/anio/net/tcp_server.h

#
# libraries
#
lib_LTLIBRARIES	= libanio.la

libanio_la_SOURCES	= anio/buffer.cpp \
			  anio/event/channel.cpp \
			  anio/event/event_loop.cpp \
			  anio/event/socket.cpp \
			  anio/log.cpp \
			  anio/net/tcp_server.cpp \
			  anio/net/connect.cpp \
			  anio/unique_fd.cpp

#
# data
#
dist_doc_DATA	= INSTALL.md LICENSE README.md

#
# tests
#
check_PROGRAMS	= test/buffer/buffer \
		  test/event_loop/event_loop \
		  test/log/fatal \
		  test/log/log \
		  test/tcp_server/tcp_server \
		  test/unique_fd/unique_fd

XFAIL_TESTS	= test/log/fatal

TESTS	= $(check_PROGRAMS)

test_buffer_buffer_SOURCES		= test/buffer/buffer.cpp

test_event_loop_event_loop_SOURCES	= test/event_loop/event_loop.cpp \
					  test/event_loop/timer_channel.cpp \
					  test/event_loop/timer_channel.h

test_log_fatal_SOURCES			= test/log/fatal.cpp
test_log_log_SOURCES			= test/log/log.cpp

test_tcp_server_tcp_server_SOURCES	= test/tcp_server/tcp_server.cpp

test_unique_fd_unique_fd_SOURCES	= test/unique_fd/unique_fd.cpp
