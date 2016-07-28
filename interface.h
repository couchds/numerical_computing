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
    BC_TYPE=1,
    IC_TYPE=2,
    EQUATION_TYPE=3,
    METHOD=4,
    TIME=5,
    GENERATE=6,
    EXIT=7
} Options;

int run(void);
int user_interface(void);
void menu(void);
int process_option(FileStructure *FileS, int choice);
void display_choices(FileStructure *FileS);

#endif /* INTERFACE_H */

