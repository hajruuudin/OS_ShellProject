//Include default libraries:
#include <stdio.h>      //IO functions like printf
#include <stdlib.h>     //General utiloty functions
#include <string.h>     //String manipulations
#include <unistd.h>     //Various system calls like fork()

//Include custom libraries:
#include "lib/print_prompt.h" //Print Prompt Header
#include "lib/constants.h"    //Constants used in code

void print_prompt(){
    char machine_name[MAX_MACHINE_LENGTH]; //This will store the name of the machine we are running on.
    char current_working_directory[1024];  //This stores the current working directory.
    char *username;                        //This stores the username retrieved at login.

    //This gets the machine name, with a max length of MAX_MACHINE_LENGTH:
    gethostname(machine_name, MAX_MACHINE_LENGTH);  
    
    //This gets the username. If the username is NULL, display an error message and exit:
    username = getlogin();  
    if(username == NULL){
        perror("ERROR - printPrompt() - getlogin - USERNAME IS NULL!");
        exit(EXIT_FAILURE);
    }

    //This gets the current working directory
    //Print error if the CWD is null or unreachable:
    if(getcwd(current_working_directory, sizeof(current_working_directory)) == NULL){ 
        perror("ERROR - printPrompt() - getcwd - DIRECTORY IS NULL!");                
        exit(EXIT_FAILURE);
    } else {
        //In the other case, store the last directory into the CWD 
        //variable using the string reverse search.
        //This is then treated as the CWD:
        char *last_directory = strrchr(current_working_directory, '/'); 
                                                                        
        if (last_directory != NULL){                                    
            last_directory++; //Go to the next /directory
        } else {
            last_directory = current_working_directory; //In case "/" was not found, just use the entire directory.
        }

        //Print the prompt with given name and color combinations. Done in the condition since "last_directory" is defined within this scope:
        printf("OSIT204-Hajrudin&Adnan-\033[1;36m%s@%s\033[0m:\033[1;33m%s\033[0m~$", username, machine_name, last_directory);
    } 
}