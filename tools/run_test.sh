#!/bin/bash

#!/bin/bash
################################################################################
# Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      #
#                                                                              #
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>#
# This is free software: you are free to change and redistribute it.           #
# There is NO WARRANTY, to the extent permitted by law.                        #
#                                                                              #
################################################################################

if (( $# < 3 ));
then
    echo "$0 <test file> <num_tests> <container_max_size>"
    exit 0
fi

(( num_tests = $2 ))

(( max_n = $3 ))

for (( n=0; n<${max_n}; n++ ));
do
    while read name mean total;
    do
        echo -n "$mean ";
    done < <($1 -r $num_tests -n $n)
    echo ""
done

