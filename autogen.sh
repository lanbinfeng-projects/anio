#!/bin/sh

echo "$0: running libtoolize"
libtoolize --install --copy || exit $?

echo "$0: running aclocal"
aclocal || exit $?

echo "$0: running autoheader"
autoheader || exit $?

echo "$0: running autoconf"
autoconf || exit $?

echo "$0: running automake"
automake --add-missing --copy || exit $?
