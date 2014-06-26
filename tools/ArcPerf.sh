#!/bin/bash

if (( $# < 3 ));
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

printf "Test "
for n in $(seq 1 $1); 
do
   printf "%d " $n
   for (( i=0; i<${tLen}; i++ ));
   do
      iTime=$(date +%s%N)
      ${Processes[$i]}
      fTime=$(date +%s%N)
     (( Total[$i] += (fTime - iTime)/1000000 ))
   done
done

echo ""

for (( i=0; i<${tLen}; i++ ));
do
   (( Means[$i] = Total[$i] / $1 ))
done

for (( i=0; i<${tLen}; i++ ));
do
   echo -e ${Processes[$i]} "\t" ${Total[$i]} "\t" ${Means[$i]}
done

# for (( i=0; i<${Processes}; i++ ));
# do
#   echo ${Means[$i]}
# done

# for i in {1..10}
# do
#    $((1+1)) 
# done