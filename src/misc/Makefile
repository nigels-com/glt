SUBDIRS = internal
CPP_SRC = string.cpp text2src.cpp timer.cpp compress.cpp image.cpp observer.cpp \
	  hex.cpp tga.cpp bmp.cpp jpeg.cpp png.cpp ppm.cpp

ROOT    = ../..
INCLUDE = -I$(ROOT)/src/png
ARCHIVE = libglt.a

default: recurse lib

include $(ROOT)/gcc/Makefile.inc

