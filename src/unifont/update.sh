#!/bin/sh

printf "#ifndef GLT_UNIFONT_H\n#define GLT_UNIFONT_H\n\n" >  unifont.h
printf "#include <unifont/config.h>\n\n"                  >> unifont.h
printf "/* Compressed GNU Unifont */\n\n"                 >  unifont.cpp
printf "extern unsigned char unicodeFont[];\n"            >> unifont.h
printf "unsigned char %s[] = \n" unicodeFont              >> unifont.cpp 
bin2src -z -ufont unifont.dat                             >> unifont.cpp
printf "\n#endif\n"                                       >> unifont.h
