#!/bin/sh

# clear variable
LIBTOOLIZE_OPTIONS=
ACLOCAL_OPTIONS=
AUTOHEADER_OPTIONS=
AUTOCONF_OPTIONS=
AUTOMAKE_OPTIONS=
FILE=

# parse options
while [ -n "$1" ]; do
	case "$1" in
		-h | --help)
			echo "Usage: $0 [OPTIONS]"
			echo
			echo "  -h, --help          display this help and exit"
			echo "  -v, --verbose       verbosely report processing"
			echo "  -c, --copy          copy files rather than symlinking them"
			echo "  -o, --output=[FILE] save output in FILE (stdout is the default)"
			exit
			;;
		-v | --verbose)
			LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --verbose"
			ACLOCAL_OPTIONS="$ACLOCAL_OPTIONS --verbose"
			AUTOHEADER_OPTIONS="$AUTOHEADER_OPTIONS --verbose"
			AUTOCONF_OPTIONS="$AUTOCONF_OPTIONS --verbose"
			AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --verbose"
			SAVE_OPTIONS="$SAVE_OPTIONS --verbose"
			shift
			;;
		-c | --copy)
			LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --copy"
			AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --copy"
			SAVE_OPTIONS="$SAVE_OPTIONS --copy"
			shift
			;;
		-o | --output)
			FILE=$2
			shift 2
			;;
		*)
			echo "$0: error: unrecognized option: '$1'" > /dev/fd/2
			echo "Try '$0 --help' for more information" > /dev/fd/2
			exit 1
	esac
done

if [ -n "$FILE" ]; then
	exec $0 $SAVE_OPTIONS > $FILE 2>&1
fi

# generate configure script

LIBTOOLIZE_OPTIONS="$LIBTOOLIZE_OPTIONS --install"
echo "$0: running: libtoolize$LIBTOOLIZE_OPTIONS"
libtoolize$LIBTOOLIZE_OPTIONS || exit $?

echo "$0: running: aclocal$ACLOCAL_OPTIONS"
aclocal$ACLOCAL_OPTIONS || exit $?

echo "$0: running: autoheader$AUTOHEADER_OPTIONS"
autoheader$AUTOHEADER_OPTIONS || exit $?

echo "$0: running: autoconf$AUTOCONF_OPTIONS"
autoconf$AUTOCONF_OPTIONS || exit $?

AUTOMAKE_OPTIONS="$AUTOMAKE_OPTIONS --add-missing"
echo "$0: running: automake$AUTOMAKE_OPTIONS"
automake$AUTOMAKE_OPTIONS || exit $?

