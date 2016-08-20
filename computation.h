#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Poly {
    // index => order... e.g. constants[2] is the coefficient for x^2.
    double *coefficients;
    int degree;
} Polynomial;
Polynomial *sum_polynomials(Polynomial *p1, Polynomial *p2);
Polynomial *multiply_polynomials(Polynomial *p1, Polynomial *p2);
int setup_computation(int argc, char *argv[], int num_procs, char *data_file_name);

#endif /* COMPUTATION_H */