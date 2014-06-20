MAINTAINERCLEANFILES = Makefile.in

if !ONLY_C_CODE

SUBDIRS = 

sbin_PROGRAMS = advaswitch

advaswitch_SOURCES = \
	main.cc \
	advaswitch.cc \
	advaswitch.h \
	cfib.cc \
	cfib.h \
	cfibentry.h \
	cfibentry.cc \
	../../adva-agent-rofl/Agent/Agent.h \
	../../adva-agent-rofl/Agent/Agent.c 


	
advaswitch_LDADD = ../../src/rofl/librofl.la 
	-lpthread \
	-lrt

AM_LDFLAGS = -static -shared `pkg-config libxml-2.0 --libs` -L"../../adva-agent-rofl/" -lSnmpAccess
AM_CPPFLAGS = -I ../../adva-agent-rofl/ `pkg-config libxml-2.0 --cflags` -std=c++0x
endif
