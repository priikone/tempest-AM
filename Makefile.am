#
#  Makefile.am
#
#  Author: Pekka Riikonen <priikone@poseidon.pspt.fi>
#
#  Copyright (C) 2001 Pekka Riikonen
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#

AUTOMAKE_OPTIONS = 1.0 no-dependencies foreign

SUBDIRS = g2-0.40

bin_PROGRAMS = tempest_am_svga tempest_am_X11

tempest_am_svga_SOURCES = \
		tempest_am_svga.c \
		signal.c \
		common.c

tempest_am_X11_SOURCES = \
		tempest_am_X11.c \
		signal.c \
		common.c

LDADD = -L./g2-0.40/ -lg2 -L/usr/X11R6/lib -lX11 -lm -lvga -lvgagl
