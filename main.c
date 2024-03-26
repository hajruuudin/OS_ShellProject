//Include default libraries for this shell:
#include <stdlib.h>  //Standard library of functions
#include <stdio.h>   //Standard input output functions
#include <string.h>  //String comparison and manipulation library

//Include custom libraries made for this shell:
#include "lib/constants.h"       //Constants
#include "lib/execute_command.h" //Command execution
#include "lib/print_prompt.h"    //Prompt printing

int main(){
    char input[MAX_INPUT_LENGTH]; //Define the actual input array of characters

    while (1) {
        print_prompt(); //Displays the prompt to the user
        fflush(stdout); //Flushes the buffer so that the output is immediately recieved

        if (fgets(input, sizeof(input), stdin) == NULL) { //Read input from the user
            printf("\n");
            break; // Exit if EOF (Ctrl+D)
        }

        input[strcspn(input, "\n")] = '\0'; //Removes any new-line characters the user might enter

        execute_command(input); //Executes the said command
    }

    return 0;
}