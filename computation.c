/**********
Daniel Couch
Numerical Computing - The Actual Computation

Description:
Data generated from interface program is used, parallel method is used to numerically solve differential equation.
**********/

#include "computation.h"

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