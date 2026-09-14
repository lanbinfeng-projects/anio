# Install ANIO

## Requirements

	g++
	make

[optional] If installing from Git repository:

	autoconf
	automake
	libtool

## Install

	./configure
	make
	make check # optional
	make install [or install-strip]

To see all of the supported configuration options,

inside the extracted source directory run:

    ./configure --help

If installing from Git repository, it is required to run first:

    autoreconf -i

