#!/bin/sh

printf "#ifndef TEXTURES_H\n#define TEXTURES_H\n\n"         > textures.h
printf "/* Include all the compiled texture sources */\n\n" > textures.cpp

for i in images/*.png;
do
	export NAME=`basename $i .png`
	export CNAME=${NAME}Texture
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME}        >> textures.h
	printf "#include \"%s\"\n" images/${NAME}.cpp         >> textures.cpp
	printf "unsigned char %s[] = \n" ${CNAME}             >  images/${NAME}.cpp 
	bin2src -z -image $i                                  >> images/${NAME}.cpp
done

printf "\n#endif\n" >> textures.h
