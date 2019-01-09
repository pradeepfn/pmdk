#!/bin/bash
#export PMEM_NO_MOVNT=1
#export PMEM_MMAP_HINT=0x0000100000000000
export PMEM_IS_PMEM_FORCE=1
LD_LIBRARY_PATH=./src/debug:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=./src/debug:$LD_LIBRARY_PATH
dir=/dev/shm/hashmap_tx-testfile
action=$1

bin="./src/benchmarks/pmembench map_insert"

if [[ $action == '-h' ]]
then
	$bin -h
elif [[ $action == '--small' ]]
then
	$bin -f $dir -d 128 -n 1024 -t 2 -r 1 -T hashmap_tx   
elif [[ $action == '--med' ]]
then
	$bin -f $dir -d 128 -n 10240 -t 2 -r 2 -T hashmap_tx   
elif [[ $action == '--large' ]]
then
	$bin -f $dir -d 128 -n 102400 -t 4 -r 2 -T hashmap_tx   
else
	exit
fi


