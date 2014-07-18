lib_LTLIBRARIES = libp3json.la

LIB_SRC = Variant.cpp 
LIB_SRC += Json.cpp
EXTRA_DIST = $(LIB_SRC)

AM_CPPFLAGS = 
AM_LDFLAGS = 

libp3json_la_CFLAGS = $(AM_CFLAGS)
libp3json_la_LDFLAGS = $(LTLDFLAGS)
libp3json_la_SOURCES = $(LIB_SRC) 

hdrdir = $(includedir)/libp3json-1.0
hdr_HEADERS = Json.h Variant.h
