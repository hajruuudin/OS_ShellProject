# IT204 - OS - Shell Project
**Students**: Hajrudin Imamovic, Adnan Mehmedovic\
**Date of submission**: 26th March 2024.\
**Project File Tasks**: NO. 5\
**Course**:Operating Systems IT 204\
**GitHub Link**: https://github.com/hajruuudin/OS_ShellProject

## File Listing / Directories
In this repository you will find:
- README.md : Guidlines and Info about he project
- makefile : Used to compile the shell into an executable file
- /lib directory : keeping the header files for the below functions and constants
- C files for main functions:
    - main.c : main function
    - execute_command.c : for command execution
    - print_prompt.: for printing the prompt

## Compiling Instructons
For the compilation of this program, run the terminal and change into this folder/directory cloned from git. Afterwards, run the command "make" in the terminal. This will automatically compile all the files using the **gcc** compiler and the following flags for error checking: **-Wall -Wextra -std=c11**. The compiled executable has the name: "os_204_shellproject". Run it using ./os_204_shellproject.

## Assignment outline and task
We were tasked with creating a simple shell interface that supports a variety of commands and acts like a normal operating system shell. The shell allows for a variety of built in commands, all of which are explained in the following block of text. The shell:
- is custom named and custom colored in the prompt
- allows for 11 different commands to be executed along with any other command, treating it as external
- is safe and has error checks for all inputs
- uses standard libraries for exeution and compilation of the commands
- suports output redirection for external commands and SOME build in commands (cat, cowsay)
- does NOT support piping (We skipped over this step as we found it tedious and for this implementation the piping function didnt really have a concrete example, other than maybe piping the output of cat into cowsay. Hence, we decied not to implement it )

### Built-in functions:

**Function**: Remove file\
**Command**: rm\
**Arguments**: filename\
**Description**: Removes a specified file from the current working directory.

**Function**: Exit shell\
**Command**: exit\
**Arguments**: none\
**Description**: Exits from the shell programme.

**Function**: Clear terminal\
**Command**: clear\
**Arguments**: none\
**Description**: Clears the termnial.

**Function**: Print file\
**Command**: cat - SUPPORTS OUTPUT REDIRECTION\
**Arguments**: filename1, filenam2... optional arguments (-c, -l, -s)\
**Description**: Copies the contents of a certain file into either the comman prompt or another output file. The additional arguments work as follows:
- Turn the output to uppercase: -c
- Turn the output to lowercase: -l
- Separate the output with special character: -s 

**Function**: Show Time\
**Command**: time\
**Arguments**: none\
**Description**: Shows the current date and time

**Function**: Rock Paper Scissors\
**Command**: rps\
**Arguments**: rock / paper / scissors \
**Description**: Plays and artifical rock, paper, scissors game against the computer. This one is more for fun :)

**Function**: Kill Procces\
**Command**: kill\
**Arguments**: pid\
**Description**: Kills the specified process, if there is one.

**Function**: Execv process\
**Command**: execv\
**Arguments**: file\
**Description**: Replaces the current process with the specified one.

**Function**: Print a cow saying a message\
**Command**: cowsay - SUPPORTS OUTPUT REDIRECTION\
**Arguments**: message\
**Description**: Prints a cow saying the said message.

**Function**: Forkbomb - CAUTION!!\
**Command**: forkbomb\
**Arguments**: none\
**Description**: Creates 20 processes running concurrently.\
LIMITED AS TO NOT CRASH THE PC. WE HEARD THIS CAN BREAK COMPUTERS SO WE WERE EXTRA CAREFUL WITH IT!!

**Function**: Secret message\
**Command**: secret\
**Arguments**: none\
**Description**: Prints a secret message to the console :)


If the said function is not found then the command will be treated as an external command and follows the regular proceddure of the fork() - exec() - wait() commands, which have been implemented in the code.

For a more descriptive and detailed analysis of how each function is implemented, please view all the individual files in the document.

## Challenges we faced and resources
Generally speaking the project was more research than it was coding. Since we were inexperienced with C, the whole proejct was a bit abstract to us since the syntax is a lot different than what we used to do. We encountered some issues with the file redirection implementation, but in the end we managed to fix it. The code implementation could have been better, however since again we are relatively new to C we decided to leave it as it is. Overall, the project itself as a coding exercise was pretty difficult, however the whole research and understanding of all the concepts was solid and intuitive. The resources we used are as follows:
- https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd - For a general overview of how the shell works and how to build a simple shell
- https://www.youtube.com/watch?v=cIBmeEpsMj0&list=PLxIRFba3rzLzxxZMMbrm_-mkI7mV9G0pj - A video documentation of building a shell
- https://youtu.be/87SH2Cn0s9A?si=iIRzYH9C9rdIqpOQ - A very quick and to-the-point course on c
- AI tools for better understanding and debugging of code
- Lectures and Labs, including this years book: "Three easy pieces"

## Answers to the Questions in the document:
> Question 1.5.1: What does the mmap() function do?

The mmap() essentialy maps files or devices into memory, allowing direct access to their contents. It takes parameters like the starting address, length, flags, file descriptor, and offset. For instance, to map a file into memory, you'd provide its file descriptor and size. Once mapped, you can read from or write to the memory region as if it were an array. This approach is efficient for large files and inter-process communication. Its similar to opening a file for writing, except now there is now direct opening but rather "mapping" for access, (sort of like a pointer). As with files, we also have to unnmap() the files at the end.

> Question 1.5.2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.

During a context switch, the OS essentialy switches or gives the performance of the CPU to a certain process. Since every process uses the CPU, we can't let one process halt the CPU indefinetly, since that would mean no other process could be finished. Because of this, the OS organises context switches through interrupts which allow it to switch the load of the CPU from one process to another chosen process.\
However, this also implies that the OS has to save the state of the process that is currently running and returning it back in a later moment. This gives a lot of overhead in the whole computer system. Because of this, we want the OS to do as few context switched as possible to reduce overhead.

> What is the output of the following code snippet? You are given that the exec system call in the child does not succeed.

Since we know that exec will replace the current process with any process specified, we can make the following conclusion: if exec fails to load, the current process will continue, meaning that "child" will be printed to the prompt. Also, the parent process has to wait for the child process to finish before it prints "parent", which is a consequence of the wait() system call.

## Other notes
No other notes are left other than the fact piping was not implemented due to these reasons:
- None of the functions in our project really require piping so we decided to leave it as just output redirection
- We have various other projects and assignmets this semester so hopefully skipping this implementation is understandable
