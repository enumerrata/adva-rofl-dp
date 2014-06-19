MAINTAINERCLEANFILES = Makefile.in

if !ONLY_C_CODE

SUBDIRS = 

sbin_PROGRAMS = etherswitch

etherswitch_SOURCES = \
	main.cc \
	etherswitch.cc \
	etherswitch.h \
	cfib.cc \
	cfib.h \
	cfibentry.h \
	cfibentry.cc \
	../../adva-agent-rofl/Agent/Agent.h \
	../../adva-agent-rofl/Agent/Agent.c 
etherswitch_LDADD = ../../src/rofl/librofl.la 
	-lpthread \
	-lrt 

AM_LDFLAGS = -static -shared `pkg-config libxml-2.0 --libs` -L"../../adva-agent-rofl/" -lSnmpAccess
AM_CPPFLAGS = -I ../../adva-agent-rofl/ `pkg-config libxml-2.0 --cflags` -std=c++0x
endif
