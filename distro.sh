#!/bin/sh

DATE=`date +%Y%m%d`
GZIP_OPTIONS=-9

function archive()
{
    FILENAME="$1"
    EXTENSIONS="$2"
    EXCLUSIONS="$3"

    TEMP1=`mktemp`
    TEMP2=`mktemp`

    for i in ${EXTENSIONS}; do 
        find -type f -name "*$i" >> ${TEMP1}; 
    done
    
    sed s/\^./glt/ ${TEMP1} | sort > ${TEMP2}
    
    for i in ${DIST_EXCLUDE}; do 
        grep -v $i ${TEMP2} > ${TEMP1}; 
        mv ${TEMP1} ${TEMP2}; 
    done
    
    tar cf ${FILENAME}.tar -T ${TEMP2} -C ../
    gzip ${GZIP_OPTIONS} ${FILENAME}.tar
    mv ${FILENAME}.tar.gz ${FILENAME}.tgz

    ls -la ${FILENAME}.tgz

    rm -f ${TEMP1} ${TEMP2}

    return
}

##
## BACKUP
##

# File matching logic for SRC backup

DIST_EXT=
DIST_EXT+=".c .h .cpp .hpp "  		# C and C++ sources and headers
DIST_EXT+=".rc .ico "		  		# Windows resources and icons
DIST_EXT+=".iss "			  		# Inno-Setup script
DIST_EXT+=".y .l "			  		# Yacc/Bison parsers and Flex scanners
DIST_EXT+=".iv "			  		# Open Inventor objects
DIST_EXT+=".dsp .dsw "         		# MSVC 6.0 projects and workspaces
DIST_EXT+=".sln .vcproj "      		# MSVC .NET projects and workspaces
DIST_EXT+=".dev "                   # Dev C++ project files
DIST_EXT+=".def "             		# MSVC DLL definition file
DIST_EXT+=".stroke "			  	# GLUT stroke fonts
DIST_EXT+=".cfg "              		# Doxygen configuration
DIST_EXT+=".txt .dox .css .html " 	# Text and HTML files
DIST_EXT+=".1 .3 .5 "				# Unix man pages
DIST_EXT+=".cg "					# NVIDIA Cg shaders
DIST_EXT+=".sh "					# Unix shell scripts
DIST_EXT+=".ok "					# Test results
DIST_EXT+=".doc "					# MS Word documents

# Path exclusion logic for SRC backup

DIST_EXCLUDE=
DIST_EXCLUDE+="^glt/bin/ "
DIST_EXCLUDE+="^glt/lib/ "
DIST_EXCLUDE+="^glt/msvc/ "
DIST_EXCLUDE+="^glt/devcpp/ "
DIST_EXCLUDE+="Makefile.win "
DIST_EXCLUDE+="^glt/doc/html/ "
DIST_EXCLUDE+="^glt/doc/man/ "
DIST_EXCLUDE+="^glt/src/Inventor/ "
DIST_EXCLUDE+="^glt/src/freetype/ "
DIST_EXCLUDE+="^glt/src/openvrml/ "
DIST_EXCLUDE+="^glt/src/gmp/ "
DIST_EXCLUDE+="^glt/src/libmng/ "
DIST_EXCLUDE+="^glt/src/cpw/ "
DIST_EXCLUDE+="^glt/src/ga/ "
DIST_EXCLUDE+="^glt/src/zzip/ "
DIST_EXCLUDE+="^glt/src/freeimage/ "
DIST_EXCLUDE+="^glt/src/purenum/ "
DIST_EXCLUDE+="^glt/src/SDL/ "
DIST_EXCLUDE+="^glt/src/SDL_image/ "
DIST_EXCLUDE+="^glt/src/SDL_mixer/ "
DIST_EXCLUDE+="~$ "
DIST_EXCLUDE+=".bak$ "
DIST_EXCLUDE+="/.# "
DIST_EXCLUDE+=".cmake$ "
DIST_EXCLUDE+="/CMakeCache.txt$ "
DIST_EXCLUDE+="/CMakeFiles/ "

archive gltSrc${DATE} "${DIST_EXT}" "${DIST_EXCLUDE}"

# File matching logic for DATA backup

DATA_EXT=
DATA_EXT+=".ppm .ppm.gz .pgm .pgm.gz .bmp .png .tga .gif .jpg "	# Images
DATA_EXT+=".fnt " 											    # Fonts
DATA_EXT+=".wrl "											    # VRML
DATA_EXT+=".dat "											    # Generic data

# File exclusion logic for DATA backup

DATA_EXCLUDE=
DATA_EXCLUDE+="^glt/bin/
DATA_EXCLUDE+="^glt/lib/
DATA_EXCLUDE+="^glt/msvc/
DATA_EXCLUDE+="^glt/devcpp/
DATA_EXCLUDE+="^glt/doc/html/
DATA_EXCLUDE+="^glt/doc/man/
DATA_EXCLUDE+="^glt/src/research/
DATA_EXCLUDE+="~
DATA_EXCLUDE+=".bak$ "
DATA_EXCLUDE+=".cmake$ "
DATA_EXCLUDE+="CMakeCache.txt$ "
DATA_EXCLUDE+="CMakeFiles$ "

archive gltData${DATE} "${DATA_EXT}" "${DATA_EXCLUDE}"

##
## DIST
##

function distro()
{
    FILENAME=$1
    ARCHIVE=$2
    INCLUSIONS="$3"
    EXCLUSIONS="$4"

    TEMP1=`mktemp`
    TEMP2=`mktemp`

    tar tzf ${ARCHIVE}.tgz > ${TEMP1}

    for i in ${INCLUSIONS}; do 
        grep $i ${TEMP1} >> ${TEMP2}; 
    done
    
    for i in ${EXCLUSIONS}; do 
        grep -v $i ${TEMP2} > ${TEMP1};
        mv ${TEMP1} ${TEMP2}
    done

    tar cf ${FILENAME}.tar -T ${TEMP2} -C ../
    gzip ${GZIP_OPTIONS} ${FILENAME}.tar
    mv ${FILENAME}.tar.gz ${FILENAME}.tgz

    ls -la ${FILENAME}.tgz

    rm -f ${TEMP1} ${TEMP2}

    return
}

GLT_VERSION=0.9-rc1

INC=
INC+="^glt/src/glt/ "
INC+="^glt/src/glutm/ "
INC+="^glt/src/fonts/ "
INC+="^glt/src/math/ "
INC+="^glt/src/mesh/ "
INC+="^glt/src/misc/ "
INC+="^glt/src/node/ "
INC+="^glt/src/zlib/ "
INC+="^glt/src/program/test/ "
INC+="^glt/src/program/util/ "
INC+="^glt/doc/ "
INC+="^glt/CMakeLists.txt "

EXC=

distro glt-core-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/program/example/ "
INC+="^glt/src/program/gltChaos/ "
INC+="^glt/src/program/gltLife/ "

EXC=
EXC+="^glt/src/program/example/unifonte "
EXC+="^glt/src/program/example/glsl "

distro glt-example-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/glut/ "
INC+="^glt/src/GL/glut "

EXC=

distro glt-glut-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/freeglut/ "
INC+="^glt/src/GL/freeglut "

EXC=

distro glt-freeglut-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/glui/ "
INC+="^glt/src/GL/glui "
INC+="^glt/src/program/glui "

EXC=

distro glt-glui-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/png/ "

EXC=

distro glt-png-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

INC=
INC+="^glt/src/jpeg/ "

EXC=

distro glt-jpeg-${GLT_VERSION} gltSrc${DATE} "${INC}" "${EXC}"

exit

GLT_GLUT=glt--${GLT_VERSION}
GLT_PNG=glt-png-${GLT_VERSION}
GLT_JPEG=glt--${GLT_VERSION}
GLT_GLUI=glt-glui-${GLT_VERSION}
GLT_ZZIP=glt-zzip-${GLT_VERSION}
GLT_CSG=glt-csg-${GLT_VERSION}

GLT_UTIL_WIN32=glt-util-win32-${GLT_VERSION}
GLT_EXAMPLE_WIN32=glt-example-win32-${GLT_VERSION}
GLT_DOX=glt-dox-${GLT_VERSION}
 
ZPR_VERSION=0.5
GLT_ZPR=glt-zpr-${ZPR_VERSION}


exit


dist-zzip:
	tar tzf gltSrc`date +%Y%m%d`.tgz         > .files
	printf ""                                > .files2
	grep "^glt/src/zzip/"             .files >> .files2
	grep "^glt/src/program/zzip/"     .files >> .files2
	grep "^glt/msvc/zzip.dsw"         .files >> .files2
	grep "^glt/msvc/zzip/"            .files >> .files2
	tar cvzf            $(GLT_ZZIP).tgz -T .files2 -C ../
	cd ..; zip -9u@ glt/$(GLT_ZZIP).zip < glt/.files2; cd glt

dist-png:

dist-jpeg:

dist-zpr:
	tar tzf gltSrc`date +%Y%m%d`.tgz        > .files
	printf ""                               > .files2
	grep "^glt/src/program/gltZpr/"	.files >> .files2
	grep "^glt/msvc/gltZpr"		.files >> .files2
	grep "^glt/gcc/"		.files >> .files2
	tar cvzf            $(GLT_ZPR).tgz -T .files2 -C ../
	cd ..; zip -9u@ glt/$(GLT_ZPR).zip < glt/.files2; cd glt
	
dist-csg:
	tar tzf gltSrc`date +%Y%m%d`.tgz         > .files
	printf ""                                > .files2
	grep "^glt/src/csg/"             .files >> .files2
	grep "^glt/src/program/csg/"     .files >> .files2
	grep "^glt/msvc/csg.dsw"         .files >> .files2
	grep "^glt/msvc/csgutil.dsw"     .files >> .files2
	grep "^glt/msvc/csg/"            .files >> .files2
	tar cvzf            $(GLT_CSG).tgz -T .files2 -C ../
	cd ..; zip -9u@ glt/$(GLT_CSG).zip < glt/.files2; cd glt

#
# WIN32 Binary Packages
#


dist-util-win32:
	find src/program/util/ -name "*.cpp" | cut -d / -f 4 > .files
	sed s/.cpp/.exe/ < .files                            > .files2
	cd msvc/Release; \
	upx -9  `cat ../../.files2`;  \
	zip -9u@ ../../$(GLT_UTIL_WIN32).zip < ../../.files2
	
dist-example-win32:
	find src/program/example/* -type d -maxdepth 0 | cut -d / -f 4 > .files
	for i in `cat .files`; do printf "%s.exe\n" $$i; done > .files2
	cd msvc/Release; \
	upx -9  `cat ../../.files2`;  \
	zip -9u@ ../../$(GLT_EXAMPLE_WIN32).zip < ../../.files2

#
# Doxygen
#

dist-doxygen:
	cd $(ROOT)
	find doc/html -type f > .files
	sed "s/^/glt\//" < .files > .files2
	tar cvzf $(GLT_DOX).tgz -T .files2 -C ../

