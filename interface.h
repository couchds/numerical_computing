#ifndef INTERFACE_H
#define INTERFACE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Data that will be written to file output. */
typedef struct FileStructure{
    // represents the type of BC.
    int bc_type;
    // represents the type of IC.
    int ic_type;
    // represents the type of PDE.
    int equation_type;
    // represents the type of solution.
    int solution_method;
    // how long to run
    double time;
    // Implement this...
    int *constants;
    // what to name the output file
    char *file_name;
} FileStructure;

typedef enum{
    BC_TYPE,
    IC_TYPE,
    EQUATION_TYPE,
    SOLUTION_METHOD,
    TIME,
    
} Options;

int run(void);
int user_interface(FileStructure *FileS, int *choices);
void menu(void);

#endif /* INTERFACE_H */

