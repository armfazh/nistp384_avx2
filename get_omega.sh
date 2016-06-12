#!/usr/bin/env bash
make clean
for i in ` seq 3 9`;
do
	export OMEGADYNAMIC=$i;
	for j in ` seq 3 9`;
	do
		export OMEGASTATIC=$j;
		make benchall > /dev/null;
	done
done


for i in ` seq 3 9`;
do
	for j in ` seq 3 9`;
	do
		./bin/bench_all_gcc_S_$((i))D_$((j));
	done
done