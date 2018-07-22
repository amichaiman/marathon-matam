#!/usr/bin/env bash

output=""

while read first last grades; do
    number_of_grades=0
    average=0
    # sum grades
    for grade in $grades; do
        let number_of_grades++
        average=`echo $average+$grade | bc`
    done
    # devide sum of grades by number of grades
    average=`echo "scale=2;$average/$number_of_grades" | bc -l`
    # add result as line in output
    output+="$first $last $average\n"
done < $1

echo -e $output | sort -k 3 -r