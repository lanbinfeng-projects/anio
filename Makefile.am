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

include_anio_HEADERS	= include/anio/log.h

#
# libraries
#
lib_LTLIBRARIES	= libanio.la

libanio_la_SOURCES	= anio/log.cpp

#
# data
#
dist_doc_DATA	= LICENSE README

#
# tests
#
check_PROGRAMS	= test/log/log

TESTS	= $(check_PROGRAMS)

test_log_log_SOURCES	= test/log/log.cpp
