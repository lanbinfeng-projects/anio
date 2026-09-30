# Install ANIO

## Requirements

	g++
	make

Debian:

	apt install g++ make

[optional] If installing from Git repository:

	autoconf
	automake
	libtool

Debian:

	apt install autoconf automake libtool

## Configure

	./configure

Install architecture-independent files in PREFIX:

	./configure --prefix=PREFIX

Display more help:

	./configure --help

If installing from Git repository, it is required to run first:

	./autogen.sh
	# or
	autoreconf -i

Display more autogen.sh help:

	./autogen.sh --help

## Build

Build programs, libraries, documentation, etc:

	make [all]

Run the test suite:

	make check

## Install

Install package:

	make install

Like install, but strip the executable files while installing them:

	make install-strip
