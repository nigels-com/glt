#!/bin/sh
#
# For more LGPL binary fonts: http://www.minigui.org/
#

printf "#ifndef GLT_FONTS_H\n#define GLT_FONTS_H\n" > fonts.h
printf "/* All the compiled font sources */\n" > fonts.cpp

# Convert VGA fonts

printf "\n/* VGA Fonts */\n\n" >> fonts.h

for i in vga/*.fnt;
do
	export NAME=`basename $i .fnt`
	export CNAME=${NAME}Font
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> fonts.h
	printf "\nunsigned char %s[] = \n" ${CNAME}    >> fonts.cpp
	bin2src -font $i                               >> fonts.cpp
done

# Convert Texture fonts

printf "\n/* Texture Fonts */\n\n" >> fonts.h

for i in texture/*.txf;
do
	export NAME=`basename $i .txf | sed s/-//`
	export CNAME=${NAME}Font
	printf "Processing %s...\n" ${NAME}
	printf "extern unsigned char %s[];\n" ${CNAME} >> fonts.h
	printf "\nunsigned char %s[] = \n" ${CNAME}    >> fonts.cpp
	bin2src -z $i                                  >> fonts.cpp
done

printf "\n#endif\n" >> fonts.h
