#!/bin/bash

### Daniel Couch
### NC_exec.sh
### Executable shell script to run both executables.
### Runs with MPI if computation used, or serial execution of interface.

### Values representing conditions.
TYPE=-1
TYPE_IS_INTERFACE=5
TYPE_IS_COMPUTATION=10
args='getopt o:f:n: $*'
count=1

### Make sure input options are all there. The two conditions are valid:
###     1. Only -o is specified, in which case we run the interface in serial.
###     2. All three options are specified.
### Otherwise, there is an error in user input.

usage="NC_exec.sh -o [option] -f [file name] -n [number of processes] \
        [option] should be either 'computation' or 'interface \
        EXAMPLE:  \
        NC_exec.sh -o computation -f data.txt -n 4 \ "

### Bash option parsing. First find which program to run.
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
### User didn't set parameter -o
if [ "${TYPE}" -eq -1 ]
then
    echo "Error. Argument -o not specified.";
    echo $usage;
    exit;
fi
if [ "${TYPE}" -eq "${TYPE_IS_INTERFACE}" ]
then
	./NC -o interface
fi
NUM_PROCS=4
DATA_FILENAME=""
### Otherwise we have two other variables to look for, and we run w/ MPI.

### Variables to check if options are selected.
PROCS_SELECTED=-1
FILENAME_SELECTED=-1

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
            FILENAME_SELECTED=0
		fi
		if [ "$i" == "-n" ]
		then
			NUM_PROCS="${!next}"
            PROCS_SELECTED=0
		fi
	done
    if [ "$FILENAME_SELECTED" -eq -1 ]
    then
        echo "Error. Argument -f not specified.";
        echo $usage;
        exit;
    fi
    if [ "$PROCS_SELECTED" -eq -1 ]
    then
###echo "Error. Argument -n not specified. Defaulting to 4 processes.";
### NUM_PROCS=4
        echo "Error. Argument -n not specified.";
        echo $usage;
        exit;
    fi
	command="mpirun -np "${NUM_PROCS}" ./NC -o computation -f ${DATA_FILENAME}"
	$command
fi