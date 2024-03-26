#MAKEFILE FOR THIS SHELL
#RUN AS "make" COMMAND IN THE TERMINAL

#SPECIFIYING THE COMPILER (gcc) AND COMPILING FLAGS THAT WILL INDICATE ERRORS AND WARNING:
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: os_204_shellproject

#INDIVIDUAL COMPILATION OF THE C FILES AND CLEAN AT THE END:
os_204_shellproject: main.o execute_command.o print_prompt.o
	$(CC) $^ -o $@

main.o: main.c lib/constants.h lib/execute_command.h lib/print_prompt.h
	$(CC) $(CFLAGS) -c $< -o $@

execute_command.o: execute_command.c lib/execute_command.h lib/constants.h
	$(CC) $(CFLAGS) -c $< -o $@

print_prompt.o: print_prompt.c lib/print_prompt.h lib/constants.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o os_204_shellproject
