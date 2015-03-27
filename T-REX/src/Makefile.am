AM_CFLAGS = -Wall -O0 -g -std=gnu11

bin_PROGRAMS = TREX
TREX_SOURCES = proxy.c main.c proxy.h
TREX_CFLAGS = $(AM_CFLAGS) -pthread -I/usr/local/include/libsoup-2.4 -I/usr/include/libxml2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
TREX_LDADD = -lsoup-2.4 -lgio-2.0 -lgobject-2.0 -lglib-2.0
TREX_LDFLAGS = -L/usr/local/lib
