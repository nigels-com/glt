# Makefile.inc
#
# A general-purpose GNU make environment for
# flexible project compilation.
#

# ----------------------------------------------------------------------

# Prevent make from printing any commands as they are executed
.SILENT:

# Delete targets when an error happens
.DELETE_ON_ERROR:

# Include user configurable settings

include $(ROOT)/gcc/Makefile.config

# Output locations for compiled programs, libraries, dependencies (.d) and object files (.o)

BIN		:= $(ROOT)/bin
LIB		:= $(ROOT)/lib

DEP		:= .depend
OBJ		:= .object

# Programs can be built from C++, C or assembler sources
# Sources includes all C, C++ and assembler sources

PROGRAMS    = $(CPP_SRC:.cpp=) $(C_SRC:.c=) $(ASM_SRC:.s=) 
SOURCES     = $(C_SRC) $(CPP_SRC) $(ASM_SRC) 

ifeq ($(TARGET),mingw32)
SOURCES += $(RES_SRC)
endif

########################################################################
#
# DEPENDENCIES

# Use the gcc compiler to determine dependencies
# OBJECTS is the set of .o files resulting from all sources
# DEPENDS is the set of .d files corresponding to each .o

DEPEND       := $(CXXFLAGS) -M -MM

OBJECTS      := $(patsubst %.cpp,$(OBJ)/%.o,$(CPP_SRC)) 
OBJECTS      += $(patsubst %.c,$(OBJ)/%.o,$(C_SRC)) 
OBJECTS      += $(patsubst %.s,$(OBJ)/%.o,$(ASM_SRC)) 

ifeq ($(TARGET),mingw32)
OBJECTS      += $(patsubst %.rc,$(OBJ)/%.o,$(RES_SRC))
endif

DEPENDS      := $(patsubst %.cpp,$(DEP)/%.d,$(CPP_SRC)) 
DEPENDS      += $(patsubst %.c,$(DEP)/%.d,$(C_SRC)) 
DEPENDS      += $(patsubst %.s,$(DEP)/%.d,$(ASM_SRC)) 

# Drag in all the dependencies, generating them
# as needed.

-include $(DEPENDS)

$(DEP)/%.d:	%.c
	printf "Makedepend %-25s\n" $*.c
	mkdir -p $(DEP)
	-$(CC) $(DEPEND) -MT $(OBJ)/$(patsubst %.c,%.o,$<) -MF $@ $< >> /dev/null
	printf "%s: %s\n" $(OBJ)/$(patsubst %.c,%.o,$<) "Makefile $(ROOT)/gcc/Makefile.inc $(ROOT)/gcc/Makefile.config" >> $@
	
$(DEP)/%.d: %.cpp 
	printf "Makedepend %-25s\n" $*.cpp
	mkdir -p $(DEP)
	-$(CXX) $(DEPEND) -MT $(OBJ)/$(patsubst %.cpp,%.o,$<) -MF $@ $< >> /dev/null
	printf "%s: %s\n" $(OBJ)/$(patsubst %.cpp,%.o,$<) "Makefile $(ROOT)/gcc/Makefile.inc $(ROOT)/gcc/Makefile.config" >> $@

########################################################################
#
# LOGGING

# Store the output to a .log file and also pipe it
# to standard output with some indentation.  
# Remove the .log file if it is empty.

LOG_BEGIN = if (!

LOG_END   = 2> $*.log) then rm -f $@; $(LOG_PROCESS); return 1; else $(LOG_PROCESS); fi

LOG_PROCESS = \
	if (test ! -s $*.log); then 									\
		rm $*.log;													\
	else															\
		cat $*.log | sed "s/^$<://" | sed "s/^/           /";		\
	fi

LOG_SUMMARY =														\
	-if (test -n "`ls *.log 2> /dev/null`"); then					\
		printf "%d warnings, %d errors in %d file(s).\n" 			\
		`cat *.log | grep warning | wc -l` 							\
		`cat *.log | grep error | wc -l` 							\
		`ls *.log | wc -w`;											\
	fi																
		
########################################################################
#
# COMPILATION

# Rules for compilation of C and C++,
# as well as recursion of subdirectories

$(OBJ)/%.o: %.cpp
	printf "Compiling  %-25s\n" $<
	mkdir -p $(OBJ)
	$(LOG_BEGIN) $(CXX) $(CXXFLAGS) -c $< -o $@ $(LOG_END)

$(OBJ)/%.o: %.c
	printf "Compiling  %-25s\n" $<
	mkdir -p $(OBJ)
	$(LOG_BEGIN) $(CC) $(CFLAGS)    -c $< -o $@ $(LOG_END)

$(OBJ)/%.o: %.s
	printf "Compiling  %-25s\n" $<
	mkdir -p $(OBJ)
	$(LOG_BEGIN) $(CXX) $(CXXFLAGS) -c $< -o $@ $(LOG_END)

$(OBJ)/%.o: %.rc
	printf "Compiling  %-25s\n" $<
	mkdir -p $(OBJ)
	$(LOG_BEGIN) windres -D__MINGW32__ $< -o $@ $(LOG_END)

.PHONY: recurse settings doRecurse summary
	
recurse: doRecurse summary

doRecurse:
	if (test "$(SUBDIRS)"); then 						\
		for i in $(SUBDIRS); do 						\
			if (test -d $$i -a -f $$i/Makefile); then 	\
				printf "Entering   %s\n" `pwd`/$$i; 	\
				$(MAKE) -C $$i;                         \
				printf "Leaving    %s\n" `pwd`/$$i; 	\
			else 										\
				printf "Skipping   %s\n" `pwd`/$$i; 	\
			fi 											\
		 done 											\
	fi													

settings:
	@if (test $(MAKELEVEL) = 0); then					\
		date;											\
		printf "\n";									\
		printf "CC       = %s\n" "$(CC)";				\
		printf "CFLAGS   = %s\n" "$(CFLAGS)";			\
		printf "CLIBS    = %s\n" "$(CLIBS)";			\
		printf "\n";									\
		printf "CXX      = %s\n" "$(CXX)";				\
		printf "CXXFLAGS = %s\n" "$(CXXFLAGS)";			\
		printf "CXXLIBS  = %s\n" "$(CXXLIBS)";			\
		printf "\n";									\
		printf "INCLUDE  = %s\n" "$(INCLUDE)";			\
		printf "\n";									\
	fi
	
summary:
	@if (test $(MAKELEVEL) = 0); then					\
		LOGS="``";										\
		printf "\nWarning summary:\n";					\
		find ./ -name "*.log";							\
	fi
	
########################################################################
#
# LINK BINARIES

.PHONY: prog

# Programs composed of simply one .cpp file are
# linked into a binary with the same name

$(BIN)/%$(EXE): $(OBJ)/%.o $(LIBS)
	mkdir -p $(BIN) 
	printf "Linking    %s\n" $(patsubst $(BIN)/%$(EXE),%$(EXE),$@)
	$(CXX) $< $(CXXLIBS) -o $@ 

# Programs composed of multiple compilation units
# linked into a binary named $(NAME)

$(BIN)/$(NAME)$(EXE): $(DEPENDS) $(OBJECTS) $(LIBS)
	mkdir -p $(BIN) 
	printf "Linking    %s\n" $(NAME)
	$(CXX) $(OBJECTS) $(CXXLIBS) -o $@ 

# Figure out which of the two previous rules should
# be triggered

prog: $(if $(NAME),$(BIN)/$(NAME)$(EXE),$(patsubst %,$(BIN)/%$(EXE),$(PROGRAMS))) 
	$(LOG_SUMMARY)

########################################################################
#
# LIBRARY MANAGEMENT

# Archive object files into static library

.PHONY: lib

$(LIB)/$(ARCHIVE)(%.o): $(OBJ)/%.o
	mkdir -p $(LIB) 
	printf "Updating %s (%s)\n" $(@F) $%
	ar cr $@ $(OBJ)/$%

# Build objects before archiving, purely for cosmetic reasons.
# Leaving out $(OBJECTS) would trigger compilation via previous rule.

lib: $(OBJECTS) $(LIB)/$(ARCHIVE)( $(patsubst $(OBJ)/%,%,$(OBJECTS) ) ) 
	$(LOG_SUMMARY)

########################################################################
#
# CLEAN

.PHONY: clean realclean

JUNK_EXT = .bak .out .log .aps .ncb .o .d .a .lib .obj .pdb .idb .pch .opt .plg ~
JUNK_DIR = .object .depend

clean:	cleantest
	printf "Cleaning   %s\n" `pwd`
	for i in $(JUNK_EXT); do rm -fv  *$$i; done
	for i in $(JUNK_DIR); do rm -Rfv $$i; done
	if (test $(ARCHIVE) ); then rm -fv $(LIB)/$(ARCHIVE); fi
	rm -fv $(OBJ) $(DEP)
	if (test "$(SUBDIRS)"); then 	    				\
		for i in $(SUBDIRS); do 						\
			if (test -d $$i -a -f $$i/Makefile); then 	\
				$(MAKE) -C $$i clean; 					\
			fi 											\
		done 											\
	fi	

########################################################################
#
# REAL-CLEAN
#
# Remove all known temporary, intermediate and otherwise unncessary files
#

realclean:
	for i in $(JUNK_EXT); do rm -fv  `find -type f -name "*$$i"`; done
	for i in $(JUNK_DIR); do rm -Rfv `find -type d -name "$$i"`; done
	
########################################################################
#
# REGRESSION TESTING

# Regression testing makes use of .ok and .out text files
# For each program, capture standard output to .out and
# compare it to .ok.  If they match, the test passes.
# However, if .out and .ok do not match it means that
# potentially a bug or feature has been introduced into
# the codebase.
#
# GLT regression tests are located in glt/src/program/test

.PHONY: cleantest

test: prog cleantest $(patsubst %,%.out,$(PROGRAMS))

%.out: $(BIN)/%$(EXE) %.ok
	printf "Testing    %-20s...  " $(patsubst $(BIN)/%,%,$<)
	$< > $@
	-@if (cmp -s $@ $(subst .out,.ok,$@)); then \
		printf "PASS\n"; 						\
	else										\
		printf "FAIL\n";						\
		diff $(patsubst %.out,%.ok,$@) $@;		\
	fi 

cleantest:
	@rm -f *.out

########################################################################
#
# SOURCE FILE FILTERING WITH EXPAND

# This rule will convert tabs to spaces and
# strip trailing whitespace from all source
# files.  This helps with version control and
# diffing.  TODO: Add DOS LF stripping here too

EXPAND    = --tabs=4

.PHONY: expand 

expand: permissions
	for i in *.c *.cpp *.h *.s *.txt *.dox; do 		      	\
		if (test -f "$$i"); then							\
			printf "Expanding  %s\n" $$i;					\
			expand $(EXPAND) $$i | sed 's/[ ]*$$//' > .tmp;	\
			if (! diff .tmp $$i >> /dev/null); then			\
				cp .tmp $$i;								\
			fi;												\
			rm .tmp;										\
		fi;													\
	done					
	if (test "$(SUBDIRS)"); then 							\
		for i in $(SUBDIRS); do 							\
			if (test -d $$i -a -f $$i/Makefile); then 		\
				$(MAKE) -C $$i expand; 						\
			fi 												\
		done 												\
	fi	

########################################################################
#
# SOURCE FILE PERMISSIONS

.PHONY: permissions

permissions:
	for i in *.c *.cpp *.h *.s *.txt *.dox Make* *.dox; do 	\
		if (test -f "$$i"); then							\
            chmod a-x,u+rw $$i;                             \
		fi;													\
	done					
	if (test "$(SUBDIRS)"); then 							\
		for i in $(SUBDIRS); do 							\
			if (test -d $$i -a -f $$i/Makefile); then 		\
				$(MAKE) -C $$i permissions; 				\
			fi 												\
		done 												\
	fi	

###################################

.PHONY: debug nothing

debug:
	echo $(DEPENDS)

nothing:

