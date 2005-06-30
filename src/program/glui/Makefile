CPP_SRC  = example1.cpp example2.cpp example3.cpp example4.cpp example5.cpp example6.cpp

ROOT     = ../../..
INCLUDE  = 

ifdef WINDIR
LIBS     = -L$(ROOT)/lib -lglui32
else
LIBS     = -L$(ROOT)/lib -lglui
endif

default: prog       

include $(ROOT)/gcc/Makefile.inc

