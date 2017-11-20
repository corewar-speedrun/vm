#!/bin/sh

EXE_PATH = "../"

mkdir test_dir

for i in *.cor; do
	echo "$i"
	./${EXE_PATH}corewar -d 230 "$i" | tail -n +3 > "test/$i.txt"
done
