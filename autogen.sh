#!/bin/sh

while [ -n "$1" ]; do
	case "$1" in
		-v | --verbose)
			LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --verbose"
			ACLOCAL_OPTIONS="$ACLOCAL_OPTIONS --verbose"
			AUTOHEADERS_OPTIONS="$AUTOHEADERS_OPTIONS --verbose"
			AUTOCONF_OPTIONS="$AUTOCONF_OPTIONS --verbose"
			AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --verbose"
			shift
			;;
		-c | --copy)
			LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --copy"
			AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --copy"
			shift
			;;
	esac
done

LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --install"
AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --add-missing"

echo "$0: running: libtoolize$LIBTOOLIZE_OPTIONS"
libtoolize$LIBTOOLIZE_OPTIONS || exit $?

echo "$0: running: aclocal$ACLOCAL_OPTIONS"
aclocal$ACLOCAL_OPTIONS || exit $?

echo "$0: running: autoheader$AUTOHEADER_OPTIONS"
autoheader$AUTOHEADER_OPTIONS || exit $?

echo "$0: running: autoconf$AUTOCONF_OPTIONS"
autoconf$AUTOCONF_OPTIONS || exit $?

echo "$0: running: automake$AUTOMAKE_OPTIONS"
automake$AUTOMAKE_OPTIONS || exit $?
