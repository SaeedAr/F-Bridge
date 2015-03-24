AM_CFLAGS = -Wall -O0 -g -std=gnu11

bin_PROGRAMS = TREX
TREX_SOURCES = proxy.c main.c proxy.h
TREX_CFLAGS = $(AM_CFLAGS) `pkg-config --cflags libsoup-2.4`
TREX_LDADD = `pkg-config --libs libsoup-2.4`
