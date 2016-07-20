/**********
Daniel Couch
Numerical Computing User Interface

Description:
User inputs the parameters of the differential equation they are solving.
**********/

#include "interface.h"

int run(void){
	FileStructure *OutputFile;
	int *valid_choices = malloc(5 * sizeof(int));
}

int user_interface(FileStructure &FileS, int *choices){
        int i = 0;
        int choice = 0;
        // Choice for integer must be between 1 and 7.
        while (choice <= 7 && choice > 0 && sizeof(choice) == 2){
                menu();
                scanf("%d", &choice);
	} 
       return 0;
}

