#!/bin/bash
################################################################################
# Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      #
#                                                                              #
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>#
# This is free software: you are free to change and redistribute it.           #
# There is NO WARRANTY, to the extent permitted by law.                        #
#                                                                              #
################################################################################

if (( $# < 2 ));
then
    echo "$0 <number of tests> <test files>"
    exit 0
fi

(( vars = 0 ))

for file in "${@:2}"
do
    Processes[$vars]=$file 
    (( vars++ ))
done

tLen=${#Processes[@]}
for (( i=0; i<${tLen}; i++ ));
do
    (( Total[$i] = 0 ))
done

for n in $(seq 1 $1); 
do
    printf "\rTest %d " $n
    for (( i=0; i<${tLen}; i++ ));
    do
        iTime=$(date +%s%N)
        ${Processes[$i]}
        fTime=$(date +%s%N)
        (( Total[$i] += (fTime - iTime) ))
    done
done

echo ""

(( MaxLength = 0 ))
for (( i=0; i<${tLen}; i++ ));
do
    Length=${#Processes[$i]}
    if (( $Length > $MaxLength ));
    then
        (( MaxLength = $Length ))
    fi

    (( Means[$i] = Total[$i] / $1 ))
done

for (( i=0; i<${tLen}; i++ ));
do
    Length=${#Processes[$i]}
    echo -n ${Processes[$i]}
    for (( j=$Length; j<${MaxLength}; j++ ));
    do
        echo -n " "
    done

    TotalTime=$(bc <<< "scale=9;${Total[$i]}/1000000000" | awk '{printf "%f", $0}') 
    Mean=$(bc <<< "scale=9;${Means[$i]}/1000000000" | awk '{printf "%f", $0}') 

    echo -e "\t" $TotalTime "\t" $Mean
done