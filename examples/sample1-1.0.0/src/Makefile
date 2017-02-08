
PROG = sample1

# TBD 
ifeq (${ARCH},arm)
	CC		= arm-linux-gnueabi-gcc-4.7
	CXX		= arm-linux-gnueabi-g++-4.7
	STRIP		= arm-linux-gnueabi-strip
	LIBTOOL		= /usr/arm-linux-gnueabi/bin/libtool
	LDFLAGS		= -L/usr/arm-linux-gnueabi/lib
	PKG_CONFIG_PATH	= /usr/arm-linux-gnueabi/lib/pkgconfig
endif

PKGCONFIG ?= pkg-config

CPPFLAGS += $(shell ${PKGCONFIG} --cflags-only-I libxml-2.0)
CPPFLAGS += $(shell ${PKGCONFIG} --cflags-only-I sqlite3)
CPPFLAGS += $(shell ${PKGCONFIG} --cflags-only-I libsystemd-daemon)

CFLAGS = \
	-ggdb -std=gnu99 \
	-fstack-protector-all \
	-D_FORTIFY_SOURCE=2 \
	-Wall -Wextra -Werror -Wformat=2 -Wstrict-aliasing=2 \
	-Wcast-align -Wwrite-strings \
	-Wfloat-equal -Wswitch-enum
LDFLAGS = \
	-ggdb -fstack-protector-all

LDFLAGS += $(shell ${PKGCONFIG} --libs-only-L libxml-2.0)
LDFLAGS += $(shell ${PKGCONFIG} --libs-only-L sqlite3)
LDFLAGS += $(shell ${PKGCONFIG} --libs-only-L libsystemd-daemon)

LDLIBS += $(shell ${PKGCONFIG} --libs-only-l libxml-2.0)
LDLIBS += $(shell ${PKGCONFIG} --libs-only-l sqlite3)
LDLIBS += $(shell ${PKGCONFIG} --libs-only-l libsystemd-daemon)


all: $(PROG)

$(PROG): $(PROG).o

clean:
	@rm -f *~ *.o $(PROG)

distclean:
	@make clean

install: $(PROG)
	install -d $(DESTDIR)/apps
	install -d $(DESTDIR)/apps/sample1
	install -d $(DESTDIR)/apps/sample1/bin
	install $(PROG) $(DESTDIR)/apps/sample1/bin/

