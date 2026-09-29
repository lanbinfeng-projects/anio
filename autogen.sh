#!/bin/sh

LIBTOOLIZE_OPTIONS="--verbose --install --copy"
ACLOCAL_OPTIONS="--verbose"
AUTOHEADER_OPTIONS="--verbose"
AUTOCONF_OPTIONS="--verbose"
AUTOMAKE_OPTIONS="--verbose --add-missing --copy"

echo "$0: running libtoolize $LIBTOOLIZE_OPTIONS"
libtoolize $LIBTOOLIZE_OPTIONS || exit $?

echo "$0: running aclocal $ACLOCAL_OPTIONS"
aclocal $ACLOCAL_OPTIONS || exit $?

echo "$0: running autoheader $AUTOHEADER_OPTIONS"
autoheader $AUTOHEADER_OPTIONS || exit $?

echo "$0: running autoconf $AUTOCONF_OPTIONS"
autoconf $AUTOCONF_OPTIONS || exit $?

echo "$0: running automake $AUTOMAKE_OPTIONS"
automake $AUTOMAKE_OPTIONS || exit $?
