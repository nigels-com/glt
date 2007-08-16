#!/bin/sh

for i in *.cpp;
do
    PROGRAM=`basename ${i} .cpp`
    ../../../bin/${PROGRAM} > ${PROGRAM}.out
    if (cmp -s ${PROGRAM}.ok ${PROGRAM}.out);
    then
        printf "Pass: %s\n" ${PROGRAM}
    else
        printf "Fail: %s\n" ${PROGRAM}
        diff ${PROGRAM}.ok ${PROGRAM}.out
    fi
done
