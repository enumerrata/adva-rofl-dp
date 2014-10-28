MAINTAINERCLEANFILES = Makefile.in

if !ONLY_C_CODE

SUBDIRS = 

sbin_PROGRAMS = polatisswitch

polatisswitch_SOURCES = \
	main.cc \
	polatisswitch.cc \
	polatisswitch.h \
	cfib.cc \
	cfib.h \
	cfibentry.h \
	cfibentry.cc \
	../../agent-hsl/Agent/Agent.h \
	../../agent-hsl/Agent/Agent.c \
	../../agent-hsl/Agent/TL1_conn.h \
	../../agent-hsl/Agent/TL1_conn.c

polatisswitch_LDADD = ../../src/rofl/librofl.la 
	-lpthread \
	-lrt

AM_LDFLAGS = -static -shared `pkg-config libxml-2.0 --libs` -L"../../agent-hsl/" -lSnmpAccess
AM_CPPFLAGS = -I ../../agent-hsl/ `pkg-config libxml-2.0 --cflags` -std=c++0x
endif
