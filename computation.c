/**********
  Daniel Couch
  Numerical Computing - The Actual Computation

Description:
Data generated from interface program is used, parallel method is used to numerically solve differential equation.
This source code implements functions used by the computation program. Another .c file will implement particular parallel algorithms to solve the PDE.
 **********/

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "computation.h"

/***********
  Functions involving manipulation of mathematical functions.
 ***********/

// Return sum of two polynomials.
Polynomial *sum_polynomials(Polynomial *p1, Polynomial *p2){
	int i;
	Polynomial *sum_polynomial;
	sum_polynomial->degree = MAX(p1->degree, p2->degree);
	sum_polynomial->coefficients = calloc(sum_polynomial->degree + 1, sizeof(double));
	for (i = 0; i < sum_polynomial->degree; i++) {
		if (i <= MIN(p1->degree, p2->degree)) {
			sum_polynomial->coefficients[i] = p1->coefficients[i] + p2->coefficients[i];
		}
		else{
			// set to higher degree'd polynomial coefficient
			(p1->degree > p2->degree) ? (p1->coefficients[i]) : (p2->coefficients[i]);
		}
	}
	return sum_polynomial;
}

// Return product of two polynomials
Polynomial *multiply_polynomials(Polynomial *p1, Polynomial *p2){
	int i, j, count, current_index;
	Polynomial *product_polynomial;
	product_polynomial->degree = p1->degree + p2->degree;
	product_polynomial->coefficients = calloc(product_polynomial->degree + 1, sizeof(double));
	count = 0;
	for (i = 0; i < p1->degree; i++) {
		for (j = 0; p2->degree; j++) {
			current_index = i + j;
			product_polynomial->coefficients[current_index] += p1->coefficients[i] * p2->coefficients[j];
		}
	}
	return product_polynomial;
}

// Arguments passed from main program.
int setup_computation(int argc, char *argv[], int num_procs, char *data_file_name){
	// Read in data from file.

	printf("%d\n", num_procs);
	// Set up MPI.
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	printf("Hello\n");



	MPI_Finalize();
}
