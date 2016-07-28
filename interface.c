/**********
Daniel Couch
Numerical Computing User Interface

Description:
User inputs the parameters of the differential equation they are solving.
**********/

#include "interface.h"

/* Source code for one of the two executables.
 */


// filler variable for initialization
#define ARBITRARY 255

#define QUIT 7
// represents invalid choice by user.
#define INVALID -10
// signals to exit program.
#define EXIT_CODE -5

#define DEBUG TRUE

int get_input(void);

int user_interface(FileStructure *FileS, int *choices){
    bool quit = false;
    int choice;
    choice = ARBITRARY;
#ifndef DEBUG
    printf("Starting user interface...\n");
#endif
    while (!quit) {
        choice = get_input();
        if (choice != INVALID) {
            process_option(choice);
        }
        if (choice == QUIT) {
            quit = true;
        }
    }
    // from here we just exit.
    return 0;
}

// Adjust value in output file struct correspind to option.
int process_option(FileStructure *FileS, int choice){
    switch (choice) {
        case BC_TYPE:
            ;
            int bc_type_choice;
            printf("Enter:\n 1 for Dirichlet BCs\n 2 for Neumann BCs\n 3 for Robin BCs\n");
            scanf("%d\n", &bc_type_choice);
            FileS->bc_type = bc_type_choice;
            break;
        case IC_TYPE:
            
            break;
        case EQUATION_TYPE:
            ;
            int equation_type_choice;
            printf("Enter:\n 1 for wave equation\n 2 for heat equation\n 3 for wave equation\n");
            scanf("%d\n", &equation_type_choice);
            FileS->equation_type = equation_type_choice;
            break;
        case SOLUTION_METHOD:
            ;
            int solution_method_choice;
            printf("Enter:\n 1 for finite-difference method\n");
            scanf("%d\n", &solution_method_choice);
            FileS->solution_method = solution_method_choice;
            break;
        case TIME:
            ;
            double time_choice;
            scanf("Enter time: %lf", &time_choice);
            FileS->time = time_choice;
            break;
        default:
            break;
    }
}

int get_input(void){
    // just a random number.
    int choice;
    choice = ARBITRARY;
    if (choice <= 7 && choice > 0 && (sizeof(choice) == 2))
    {
        return choice;
    }
    else{
        printf("The value %d is an invalid choice\n", choice);
        return INVALID;
    }
}


void menu(void){
    printf("1. Modify boundary conditions.\n");
    printf("2. Modify initial conditions.\n");
    printf("3. Modify PDE.\n");
    printf("4. Set runtime.\n");
    printf("5. Select numerical method.\n");
    printf("6. Generate job submission.\n");
    printf("7. Exit\n");
}

// Create the txt file containing the information for the equation.
int write_to_output(FileStructure *OutputFile;){
    // LINE 1: BC
    return 0;
}