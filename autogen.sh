#!/bin/sh

libtoolize --copy --install && \
	aclocal && \
	autoheader && \
	autoconf && \
	automake --add-missing --copy
