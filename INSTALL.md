# Install ANIO

## Requirements

	g++
	make

[optional] If installing from Git repository:

	autoconf
	automake
	libtool

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

## Build

Build programs, libraries, documentation, etc:

	make [all]

Run the test suite:

	make check # optional

## Install

Install package:

	make install

Like install, but strip the executable files while installing them:

	make install-strip
