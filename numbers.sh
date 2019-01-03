#!/usr/bin/env bash

declare -a arr=("ctree")
#declare -a lt=("seq")
declare -a lt=("seq" "tsxseq" "redofence" "redonofence" "tsxredofence" "tsxredonofence" "undofence" "undonofence" "tsxundofence" "tsxundonofence")

for bm in "${arr[@]}"
do
	mkdir -p results/"$bm"
	for l in "${lt[@]}"
	do
		./runscript.py -c -w "$bm" -lt "$l"
		./runscript.py -b -w "$bm" -lt "$l"
		./runscript.py -r -w "$bm" -lt "$l" > results/"$bm"/"$bm"_t1_"$l".txt
		#./runscript.py -r -w "$bm" -lt "$l"
	done
done
exit



