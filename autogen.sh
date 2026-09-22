#!/bin/sh

libtoolize --install --copy || exit $?

aclocal || exit $?

autoheader || exit $?

autoconf || exit $?

automake --add-missing --copy || exit $?
