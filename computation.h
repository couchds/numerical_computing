#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int setup_computation(int argc, char *argv[], int num_procs, char *data_file_name);

#endif COMPUTATION_H
