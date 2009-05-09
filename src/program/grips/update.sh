#!/bin/sh

##
## Convert textures to source
##

printf "#ifndef GRIPS_TEXTURES_H\n#define GRIPS_TEXTURES_H\n\n" > textures.h
printf "/* Include all the compiled texture sources */\n\n"     > textures.cpp

for i in media/*.pgm;
do
	NAME=`basename $i .pgm`
	CNAME=${NAME}Texture
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> textures.h
	printf "#include \"%s\"\n" media/${NAME}.cpp   >> textures.cpp
	bin2src -c -image -alpha -n ${CNAME} $i        >  media/${NAME}.cpp
done

for i in media/*.tga;
do
	NAME=`basename $i .tga`
	CNAME=${NAME}Texture
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> textures.h
	printf "#include \"%s\"\n" media/${NAME}.cpp   >> textures.cpp
	bin2src -c -image -n ${CNAME} $i               >  media/${NAME}.cpp
done

for i in media/*.png;
do
	NAME=`basename $i .png`
	CNAME=${NAME}Texture
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> textures.h
	printf "#include \"%s\"\n" media/${NAME}.cpp   >> textures.cpp
	bin2src -c -image -n ${CNAME} $i               >  media/${NAME}.cpp
done

printf "\n#endif\n" >> textures.h

##
## Convert examples to source
##


printf "#ifndef GRIPS_EXAMPLES_H\n#define GRIPS_EXAMPLES_H\n\n" > examples.h
printf "/* Example setups */\n\n"                               > examples.cpp

EXAMPLES=

for i in examples/*.dat;
do
	NAME=`basename $i .dat`
	CNAME=${NAME}Example
	EXAMPLES="${EXAMPLES} ${CNAME}"
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME}  >> examples.h
	bin2src -u -z -n ${CNAME} $i                    >>  examples.cpp
done

##
## Create NULL terminated list of examples
##

printf "\nextern unsigned char *examples[];\n" >> examples.h
printf "\nunsigned char *examples[] = \n{\n"   >> examples.cpp

for i in ${EXAMPLES};
do
	printf "\t%s,\n" $i             >> examples.cpp
done
printf "\t0\n};\n"                      >> examples.cpp

printf "\n#endif\n" >> examples.h

