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

include_anio_HEADERS	= include/anio/event_loop.h \
			  include/anio/fd_guard.h \
			  include/anio/log.h

#
# libraries
#
lib_LTLIBRARIES	= libanio.la

libanio_la_SOURCES	= anio/event_loop.cpp \
			  anio/fd_guard.cpp \
			  anio/log.cpp

#
# data
#
dist_doc_DATA	= LICENSE README.md

#
# tests
#
check_PROGRAMS	= test/event_loop/event_loop \
		  test/fd_guard/fd_guard \
		  test/log/log

TESTS	= $(check_PROGRAMS)

test_event_loop_event_loop_SOURCES	= test/event_loop/event_loop.cpp

test_fd_guard_fd_guard_SOURCES		= test/fd_guard/fd_guard.cpp

test_log_log_SOURCES			= test/log/log.cpp
