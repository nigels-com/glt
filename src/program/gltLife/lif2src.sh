#!/bin/bash

printf "#ifndef LIF2SRC_H\n#define LIF2SRC_H\n\n" > lif2src.h
printf "#include \"lif2src.h\"\n\n" > lif2src.cpp

printf "#ifndef EXAMPLE_H\n#define EXAMPLE_H\n\n" > example.h
printf "#include \"lif2src.h\"\n\nconst void *lifeExamples[]={\n" >> example.h

for i in *.LIF; 
	do declare NAME=`echo $i | cut -d. -f1 | sed s/-/_/`; 
	echo $NAME;
	printf "extern const unsigned char %s[];\n" $NAME >> lif2src.h;
	printf "\nconst unsigned char %s[] = \n"      $NAME >> lif2src.cpp;
	bin2src -z -u $i                             >> lif2src.cpp;	
	printf "\t\"%s\",\t%s,\n" $NAME $NAME >> example.h;
done

printf "\n#endif\n" >> lif2src.h
printf "\tNULL,\tNULL\n};\n\n#endif\n" >> example.h;
