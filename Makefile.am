AUTOMAKE_OPTIONS	= foreign subdir-objects

ACLOCAL_AMFLAGS	= -I m4

#
# flags
#
AM_CPPFLAGS	= -Iinclude
LDADD		= ./libanio.la

#
# headers
#
include_aniodir	= $(includedir)/anio

include_anio_HEADERS	= include/anio/channel.h \
			  include/anio/event_loop.h \
			  include/anio/log.h \
			  include/anio/unique_fd.h

#
# libraries
#
lib_LTLIBRARIES	= libanio.la

libanio_la_SOURCES	= anio/channel.cpp \
			  anio/event_loop.cpp \
			  anio/log.cpp \
			  anio/unique_fd.cpp

#
# data
#
dist_doc_DATA	= LICENSE README.md

#
# tests
#
check_PROGRAMS	= test/event_loop/event_loop \
		  test/log/log \
		  test/unique_fd/unique_fd

TESTS	= $(check_PROGRAMS)

test_event_loop_event_loop_SOURCES	= test/event_loop/event_loop.cpp \
					  test/event_loop/timer_channel.cpp

test_log_log_SOURCES			= test/log/log.cpp

test_unique_fd_unique_fd_SOURCES			= test/unique_fd/unique_fd.cpp
