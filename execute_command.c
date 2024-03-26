//Include default libraries
#include <stdio.h>      //IO functions like printf
#include <stdlib.h>     //General utiloty functions
#include <string.h>     //String manipulations
#include <unistd.h>     //Various system calls like fork()
#include <sys/types.h>  //Datatypes for system related functions
#include <sys/wait.h>   //Wait function for holding child processes
#include <time.h>       //Date and time
#include <ctype.h>      //ToUpper and ToLower in CAT function
#include <signal.h>     //For implementation of the kill() command

//Include custom libraries:
#include "lib/execute_command.h" //Execute Commands Header
#include "lib/constants.h"       //Constants used in code

void execute_command(char *command){
    //TOKENIZING: 
    char *arguments[MAX_INPUT_LENGTH];  //Define the arguments array with a max input size
    char *token = strtok(command, " "); // Tokenize the command based on " ":

    int i = 0;
    //As long as this is true, add tokens/arguments into the arguments array:
    while(token != NULL && i < MAX_INPUT_LENGTH - 1){ 
        arguments[i++] = token;
        token = strtok(NULL, " ");
    }

    //The last argument has to be NULL, in order to know where the prompt ends:
    arguments[i] = NULL;

    //OUTPUT REDIRECTION CHECK:
    int is_redirection_requred = 0; //Initially, the check is false (0):
    char *output_file = NULL;       //The file is also NULL
    for (int j = 0; arguments[j] != NULL; j++) {
        if (strcmp(arguments[j], ">") == 0) { //Check is the ">" character is present:
            if (arguments[j + 1] != NULL) { //If the file is specified, procees with declaration
                is_redirection_requred = 1;
                output_file = arguments[j + 1];
                for (int k = j; arguments[k] != NULL; k++) {
                    arguments[k] = arguments[k + 2]; //Skip over the last two elements: ">" and filename
                }
                break;
            } else { //In case the file is not specified:
                perror("ERROR - redirectionCheck - FILENAME NOT SPECIFIED!");
                exit(EXIT_FAILURE);
            }
        }
    }

    //BUILT IN COMMANDS:
    if (strcmp(command, "rm") == 0) // Remove said file from working directory:
    {
        if(arguments[1] == NULL){
            fprintf(stderr, "Command: rm - Format: rm <filename>\n");
            return;
        } 

        if(remove(arguments[1]) == 0){
            printf("%s removed successfully.\n", arguments[1]);
        } else {
            perror("ERROR - command: rm - ERROR WHILE REMOVING FILES!");
        }
    }
    else if (strcmp(command, "exit") == 0) // Exit the shell:
    {
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(command, "clear") == 0) // Clear the Shell:
    {
        printf("\033[H\033[2J"); //Clear shell escape code
    }
    else if (strcmp(command, "cat") == 0) //CAT implementation with -l -c and -s arguments and file redirection(VIEW README FOR MORE INFO!!):
    {
        if(arguments[1] == NULL){
            fprintf(stderr, "Command: cat - Format: cat <filename1> <filename2...> {optional format argument}\n");
            return;
        }

        int prompt_length = 0; //Check the length of the arguments prompt:
        for(int i = 1; arguments[i] != NULL; i++){
            prompt_length++;
        }

        int transform_flag; //Initialise variables for checking optional arguments
        int optional_argument = 0;
        if(strcmp(arguments[prompt_length], "-c") ==0 ){ 
            transform_flag = 1; //This means that the output will be capitalized
        } else if (strcmp(arguments[prompt_length], "-l") == 0){
            transform_flag = 2; //This means that the output will be in lowercase
        } else if (strcmp(arguments[prompt_length], "-s") == 0){
            transform_flag = 3; //This will make the output have spaces in between
        } else {
            transform_flag = 0; //This leaves the output as it is with no optional arguments
            optional_argument = 1;
        }

        for(int i = 1; arguments[i + 1 - optional_argument] != NULL; i++){
            FILE *file = fopen(arguments[i], "r"); //Open the file in read mode
            if(file == NULL){
                perror("ERROR - command: cat - input specified file is NULL!");
                continue;
            }

            if(is_redirection_requred) //If redirection is specified, redirect it to the said output file
            {
                FILE *output = fopen(output_file, "w");
                if(output == NULL){
                    perror("ERROR - comman: cat - output file is not specified!");
                    return;
                }

                int c;
                while ((c = fgetc(file)) != EOF) {
                    if(transform_flag == 1)
                    {
                        fputc(toupper(c), output);
                    } 
                    else if (transform_flag == 2)
                    {
                        fputc(tolower(c), output);
                    } 
                    else if (transform_flag == 3)
                    {
                        fputc(c, output);
                        fputc('-', output);
                    } 
                    else 
                    {
                        fputc(c, output);
                    }
                }

                fclose(output);
            }
            else //Otherwise, just output the cat to the console
            {
                int c;
                while ((c = fgetc(file)) != EOF) {
                    if(transform_flag == 1)
                    {
                        putchar(toupper(c));
                    } 
                    else if (transform_flag == 2)
                    {
                        putchar(tolower(c));
                    } 
                    else if (transform_flag == 3)
                    {
                        putchar(c);
                        putchar((int)' ');
                    } 
                    else 
                    {
                        putchar(c);
                    }
                }
                fclose(file);
            }
        }
    }
    else if (strcmp(command, "cowsay") == 0) //COWSAY implementation with file redirection:
    {
        if (arguments[1] == NULL) {
            fprintf(stderr, "Command: cowsay - Format: cowsay <message>\n");
            return;
        }

        if(is_redirection_requred) //If we want to output the message into a new file:
        {
            FILE *file = fopen(output_file, "w");
            if(output_file == NULL){
                perror("Error in function: cowsay | OUTPUT FILE NOT SPECIFIED");
                return;
            }

            fprintf(file, " _____\n");
            fprintf(file,"< %s >\n", arguments[1]);
            fprintf(file," -----\n");
            fprintf(file,"        \\   ^__^\n");
            fprintf(file,"         \\  (oo)\\_______\n");
            fprintf(file,"            (__)\\       )\\/\\\n");
            fprintf(file,"                ||----w |\n");
            fprintf(file,"                ||     ||\n");

            fclose(file);

        } 
        else //If we want to print it to the console:
        {
            printf(" _____\n");
            printf("< %s >\n", arguments[1]);
            printf(" -----\n");
            printf("        \\   ^__^\n");
            printf("         \\  (oo)\\_______\n");
            printf("            (__)\\       )\\/\\\n");
            printf("                ||----w |\n");
            printf("                ||     ||\n");
        }
    }
    else if (strcmp(command, "rps") == 0) //Rock Paper Scissors game in the terminal, because why not :D:
    {
        if (arguments[1] == NULL) {
            fprintf(stderr, "Command: rps - Format: rps <rock/paper/scissors>\n");
            return;
        }

        char *options[3] = {"rock", "paper", "scissors"}; //Create three options for the computer to choose:

        srand(time(NULL));
        int computer_choice = rand() % 3; //Generate random index for the choise

        int player_choice = -1;

        for (int i = 0; i < 3; i++) { //See if the player made a valid decision
            if (strcmp(arguments[1], options[i]) == 0) {
                player_choice = i;
                break;
            }
        }

        if (player_choice == -1) //In case the play did invalid input:
        {
            fprintf(stderr, "Invalid choice. Please choose rock, paper, or scissors.\n");
        }

        if ((player_choice + 1) % 3 == computer_choice) //In case the input is valid, exhaustive cases apply:
        {
            printf("You lost! Your choice: \033[1;36m%s\033[0m - The Computer's Choice: \033[1;32m%s\033[0m\n", options[player_choice], options[computer_choice]);
        } 
        else if (player_choice == computer_choice) 
        {
            printf("It's a tie! Your choice: \033[1;36m%s\033[0m - The Computer's Choice: \033[1;32m%s\033[0m\n", options[player_choice], options[computer_choice]);
        } 
        else 
        {
            printf("You won! Your choice: \033[1;36m%s\033[0m - The Computer's Choice: \033[1;32m%s\033[0m\n", options[player_choice], options[computer_choice]);
        }
    }
    else if (strcmp(command, "time") == 0) //Time command to show the current time and date:
    {
        time_t t;
        time(&t);

        printf("It is currently \033[1;36m%s\033[0m", ctime(&t));
    }
    else if (strcmp(command, "secret") == 0) //Little secret command ^__^
    {
        printf("Hajrudin Imamovic and Adnan Mehmedovic are the best! :)\n");
    }
    else if (strcmp(command, "kill") == 0) //Kill command to kill processes:
    {
        if (arguments[1] == NULL) {
            fprintf(stderr, "Command: kill - Format: kill <pid>\n");
            return;
        }

        pid_t pid = atoi(arguments[1]);
        if (kill(pid, SIGTERM) == -1) {
            perror("ERROR: command - kill - PROCESS COULD NOT BE FOUND!");
        } else {
            printf("Process with PID %d killed.\n", pid);
        }
    } 
    else if (strcmp(command, "execv") == 0) //Execv command to replace current process with any other specified process:
    {
        if (arguments[1] == NULL) {
            fprintf(stderr, "Command: execv - Format: execv <executable>\n");
            return;
        }
        if (execv(arguments[1], arguments + 1) == -1) {
            perror("ERROR: command - execv - EXECUTABLE COULD NOT BE LOADED!");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(command, "forkbomb") == 0) //Forkbomb implementation for 20 processes !CAUTION!:
    {
        printf("Executing forkbomb. Please be ready for system slowdown!\n");
        int process_num;
        
        for(process_num = 0; process_num <= MAX_PROCESSES; process_num++){
            pid_t pid = fork();
            if(pid == 0){
                printf("HAHAHA A CHILD PROCESS HAS BEEN CREATED! %d\n", getpid());
                while(1);
                exit(EXIT_SUCCESS);
            } else if (pid < 0){
                perror("Forking error! Forkbomb denied, for now...");
                break;
            }
        }
        if (process_num == MAX_PROCESSES ){
            printf("Fork bomb done! You survived...");
        }
    }
    else //If the process is not buil-it, run it as an external process using fork(), exec() and wait():
    {
        pid_t pid = fork();
        if (pid == -1) {
            // Fork failed
            perror("ERROR: external command - FORK FAILED!");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
             // Child process
            if (is_redirection_requred) {
                FILE *fd = fopen(output_file, "w");
                if (fd == NULL) {
                    perror("ERROR: external command - OUTPUT FILE UNDEFINED!");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fileno(fd), STDOUT_FILENO) == -1) {
                    perror("ERROR: external command - DUPLICATE FILE DESCRIPTOR ERROR!");
                    exit(EXIT_FAILURE);
                }
                fclose(fd);
            }

            if (execvp(arguments[0], arguments) == -1) {
                perror("ERROR: external command - EXECVP ERROR!");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            if (wait(&status) == -1) {
                perror("ERROR: external command - WAIT ERROR");
                exit(EXIT_FAILURE);
            }
        }
    }
}