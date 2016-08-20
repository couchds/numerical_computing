/**********
  Daniel Couch
  Numerical Computing User Interface

Description:
User inputs the parameters of the differential equation they are solving.
Output file to be parsed... (will remove this later).
 **********/

/*
	TO DO
	After implementing solution, rewrite this so a file doesn't have to be generated, but the user can just input the settings
	and init the processes.
*/

#include "interface.h"

// filler variable for initialization
#define ARBITRARY 255
#define QUIT 8
// represents invalid choice by user.
#define INVALID -10
// valid choice
#define VALID 10
// signals to exit program.
#define EXIT_CODE -5
#define DEBUG 1


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
	char filename[ARBITRARY];
} FileStructure;

typedef enum{
	BC_TYPE=1,
	IC_TYPE=2,
	EQUATION_TYPE=3,
	METHOD=4,
	TIME=5,
	FILENAME=6,
//	CONSTANTS=7,
	GENERATE=7,
	EXIT=8
} Options;

int user_interface(void);
int run(void);
void menu(void);
int equation_construction(void);
int process_option(FileStructure *FileS, int *choices_valid_array, int choice);
void display_choices(FileStructure *FileS, int *choices);
int get_user_input(void);

/********* Move everything above into header when done with this part. **********/


int user_interface(void){
	// choices must all be selected in order to create the output file.
	int *choices_valid_array = malloc(10*sizeof(int));
	int i = 0;
	for (i = 0; i <= 10; i++){
		choices_valid_array[i] = INVALID;
	}
	double time_choice;
	FileStructure *FileS = malloc(sizeof(FileStructure));
	bool quit = false;
	int user_choice = ARBITRARY;
#ifdef DEBUG
	printf("[DEBUG] Starting user interface...\n");
#endif
	while (!quit) {
#ifdef DEBUG
		printf("[DEBUG] Starting loop in user interface...\n");
#endif
		//display_choices(FileS, choices);
		menu();
		user_choice = get_user_input();
		if ((user_choice <= 7) && (user_choice > 0))
        	{
                	// set choice to be filled.
                	choices_valid_array[user_choice] = VALID;
			process_option(FileS, choices_valid_array, user_choice);
        	}
		else{
			// invalid choice.
			printf("Invalid choice: %d\n", user_choice);
		}
		if (user_choice == QUIT) {
			quit = true;
		}
	}
	free(choices_valid_array);
	// from here we just exit.
	return 0;
}

// Adjust value in output file struct correspond to option.
int process_option(FileStructure *FileS, int *choices_valid_array, int choice){
	switch (choice) {
		case BC_TYPE:
			;
			printf("Enter:\n 1 for Dirichlet BCs\n 2 for Neumann BCs\n 3 for Robin BCs\n");
			FileS->bc_type = get_user_input();
			choices_valid_array[BC_TYPE-1] = VALID;
			break;
		case IC_TYPE:
			printf("Enter:\n 1 for ...\n");
			FileS->ic_type = get_user_input();
			choices_valid_array[IC_TYPE-1] = VALID;
			break;
		case EQUATION_TYPE:
			;
			printf("Enter:\n 1 for wave equation\n 2 for heat equation\n 3 for wave equation\n");
			FileS->equation_type = get_user_input();
			choices_valid_array[EQUATION_TYPE-1] = VALID;	
			break;
		case METHOD:
			;
			printf("Enter:\n 1 for finite-difference method\n");
			FileS->solution_method = get_user_input();
			choices_valid_array[METHOD-1] = VALID;
			break;
		case TIME:
			;
			double time_choice;
			char input_buffer[ARBITRARY];
			printf("Enter runtime:\n");
			printf("$NCUI $ ");
			fgets(input_buffer, sizeof(input_buffer), stdin);
		        time_choice = atof(input_buffer);
			printf("HERE\n");
			FileS->time = time_choice;
			choices_valid_array[TIME-1] = VALID;
			break;
		case FILENAME:
			;
			char input_buffer2[ARBITRARY];
			fgets(input_buffer2, sizeof(input_buffer2), stdin);
			strcpy(FileS->filename, input_buffer2);
			choices_valid_array[FILENAME-1] = VALID;
			break;
		case GENERATE:
			;
			write_to_output(FileS, choices_valid_array);
		case EXIT:
			return EXIT_CODE;
		default:
			break;
	}
}

// TO DO:
// Write to display current settings.
void display_choices(FileStructure *FileS, int *choices){
	int i;
	char *choice_types[] = {"Boundary Condition Class", "Initial Condition Class", "Equation Class", "Method of Solution", "Runtime"};
	for (i = 0; i < 6; i++) {
		// Display which choices have not been made.
		if (choices[i] != VALID) {
			int option_number = i + 1;
			printf("Not selected: %s (Option number %d", choice_types[i], option_number);
		}
		// Rewrite this once boundary conditions have been implemented.
		switch (i) {
			case 1:
				printf("Boundary conditions:\n");
				break;

			default:
				break;
		}
	}
}

// Create an equation based on user input.
//int equation_construction(void){
//	bool quit = false;
//	while (!quit) {
//		// Get user input
//
//	}
//}

double get_equation_input(){
	double coefficient_value;
	int success = scanf("%d", &coefficient_value);
	if (!success) {
		// perror()
		// printf("Invalid option: %d\n", coefficient_value);
		return -1;
	}
	return;
}

void menu(void){
	printf("$NCUI$ 1. Modify boundary conditions.\n");
	printf("$NCUI$ 2. Modify initial conditions.\n");
	printf("$NCUI$ 3. Modify PDE.\n");
	printf("$NCUI$ 4. Select numerical method.\n");
	printf("$NCUI$ 5. Set runtime.\n");
	printf("$NCUI$ 6. Set file name.\n");
	printf("$NCUI$ 7. Generate job submission.\n");
	printf("$NCUI$ 8. Exit\n");
}

// Create the txt file containing the information for the equation.
int write_to_output(FileStructure *OutputFile, int *choices_array){
	int i;
	// Check if all choices have been made.
	for (i = 0; i < 5; i++){
		if (choices_array[i] != VALID){
			printf("Invalid choice %d\n", choices_array[i]);
			return -1;
		}
	}
	if (access(OutputFile->filename, F_OK) != -1){
		perror("File: %s already exists.\n");
		return -1;
	}
	FILE *fho = fopen(OutputFile->filename, "w");
	printf("REACHED HERE\n");
	// First line: BC
	fprintf(fho, "%d\n", OutputFile->bc_type);
	// Second: IC
	fprintf(fho, "%d\n", OutputFile->ic_type);
	// Third: Equation type
	fprintf(fho, "%d\n", OutputFile->equation_type);
	// Fourth: Solution
	fprintf(fho, "%d\n", OutputFile->solution_method);
	// Fifth: Runtime
	fprintf(fho, "%f.3\n", OutputFile->time);
	fclose(fho);
	return 0;
}

// Retrieve user choice from stdin   (integer)
int get_user_input(void){
	char input_buffer[ARBITRARY];
	char *input_end;
	int user_choice;
	printf("$NCUI$ ");
	fgets(input_buffer, sizeof(input_buffer), stdin);
	user_choice = strtol(input_buffer, &input_end, 10);
	return user_choice;
}

