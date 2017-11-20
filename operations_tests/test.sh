#!/bin/sh

EXE_PATH = "../vm/"

mkdir test_dir

for i in *.cor; do
	echo "$i"
	./${EXE_PATH}corewar -d 230 "$i" | tail -n +3 > "test/$i.txt"
done
