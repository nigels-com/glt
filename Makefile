SUBDIRS = src
ROOT    = .
INCLUDE =

.PHONY: setup archive doxygen backup-src backup-data dos2unix realclean

default: setup recurse

setup:
	if test ! -d bin; then mkdir bin; fi
	if test ! -d lib; then mkdir lib; fi
	
archive: backup-src backup-data

doxygen: doc/doxygen.cfg
	cd doc; doxygen doxygen.cfg; cd ..

doxygen-clean:
	rm -Rf doc/html
	rm -Rf doc/man

dos2unix:
	dos2unix `find -type f -name "*.h"`
	dos2unix `find -type f -name "*.hpp"`
	dos2unix `find -type f -name "*.cpp"`
	dos2unix `find -type f -name "*.c"`
	dos2unix `find -type f -name "*.sh"`
	dos2unix `find -type f -name "*.def"`
	dos2unix `find -type f -name "*.y"`
	dos2unix `find -type f -name "*.l"`
	dos2unix `find -type f -name "*.txt"`
	dos2unix `find -type f -name "Make*"`
	dos2unix `find -type f -name "*.stroke"`
	dos2unix `find -type f -name "*.dox"`
	dos2unix `find -type f -name "*.iss"`
	dos2unix `find -type f -name "*.rc"`
	dos2unix `find -type f -name "*.cfg"`

realclean: clean doxygen-clean
	rm -fv lib/* bin/*
	rm -fv `find -name core`
	rm -fv `find -name "*.o"`

include $(ROOT)/gcc/Makefile.inc
include $(ROOT)/gcc/Makefile.dist
