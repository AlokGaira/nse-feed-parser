#!/bin/sh

patch -p1 < patch.diff
./configure --build=mingw32 --host=mingw32 --enable-shared \
 	    --prefix=/mingw
(cd src && make -f Makefile.lib)
