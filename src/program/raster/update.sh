#!/bin/sh

##
## Convert textures to source
##

printf "#ifndef MEDIA_H\n#define MEDIA_H\n\n"     > media.h
printf "/* Include all the compiled media */\n\n" > media.cpp

for i in textures/*.png;
do
	NAME=`basename $i .png`
	CNAME=${NAME}Texture
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME}   >> media.h
	printf "#include \"%s\"\n" textures/${NAME}.cpp  >> media.cpp
	printf "unsigned char %s[] = \n" ${CNAME}        >  textures/${NAME}.cpp 
	bin2src -z -image $i >> textures/${NAME}.cpp
done

#

printf "\n\n" >> media.h

for i in models/*.ase;
do
	NAME=`basename $i .ase`
	CNAME=${NAME}Model
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> media.h
	printf "#include \"%s\"\n" models/${NAME}.cpp  >> media.cpp
	printf "unsigned char %s[] = \n" ${CNAME}      >  models/${NAME}.cpp 
	bin2src -z -u $i >> models/${NAME}.cpp
done

printf "\n#endif\n" >> media.h

