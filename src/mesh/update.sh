#!/bin/sh

printf "\nGenerating vrmlpars.cpp...\n"

bison vrmlpars.y -dv --no-lines -p Vrml -o vrmlpars.cpp 
rm vrmlscan.h
mv vrmlpars.hpp vrmlscan.h

printf "\nGenerating vrmlscan.cpp...\n"

flex -v -PVrml vrmlscan.l
rm vrmlscan.cpp
mv lex.Vrml.c vrmlscan.cpp

