# Copyright (C) 2020 Megan Ruggiero
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

.POSIX:
.PHONY: all clean install uninstall

CFLAGS		= -D PKGVER=\"git-`git rev-parse HEAD`\"
LDFLAGS		= -l m
INSTALL		= install
INSTALL_PROGRAM	= $(INSTALL)
DESTDIR		=
prefix		= /usr/local
exec_prefix	= $(prefix)
bindir		= $(exec_prefix)/bin

all: catlol

catlol:

clean:
	rm -f catlol

install: all
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) catlol $(DESTDIR)$(bindir)/catlol

uninstall:
	rm -f $(DESTDIR)$(bindir)/catlol
