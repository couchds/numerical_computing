#!/bin/bash

# Executable shell script to run the program.
# Runs with MPI if computation used, or serial execution of interface.
TYPE=-1
TYPE_IS_INTERFACE=5
TYPE_IS_COMPUTATION=10
args='getopt o:f:n: $*'
count=1
for i
do
	count=$((count+1))
	next=$count
	echo "${!next}"
	if [ "$i" == "-o" ]
	then
		if [ "${!next}" == "computation" ]
		then
			TYPE=${TYPE_IS_COMPUTATION}
		fi
		if [ "${!next}" == "interface" ]
		then
			TYPE=${TYPE_IS_INTERFACE}
		fi
	fi
done
if [ "${TYPE}" -eq "${TYPE_IS_INTERFACE}" ]
then
	./NC -o interface
fi
NUM_PROCS=4
DATA_FILENAME=""
# otherwise we have two other variables to look for, and we run w/ MPI.
count=1
if [ "$TYPE" -eq "$TYPE_IS_COMPUTATION" ]
then
	for i
	do
	count=$((count+1))
	next=$count
		if [ "$i" == "-f" ]
		then
			DATA_FILENAME="${!next}"
		fi
		if [ "$i" == "-n" ]
		then
			NUM_PROCS="${!next}"
		fi
	done
	command="mpirun -np "${NUM_PROCS}" ./NC -o computation -f ${DATA_FILENAME}"
	$command
fi
