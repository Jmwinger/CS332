# Pipe Command Executor 

A simple C program that shows process communication
using popen() and pclose(). The program acts as a basic shell,
which lets users to enter commands and display their
output. The program continues accepting commands until the
user enters "quit".

## Requirements

- GCC compiler

## Compile

```bash
gcc -Wall -Wextra -o lab11  lab11.c

Example

Before execution:

./lab11

After execution: 

Enter command: ls *.c
hello.c
lab01prime.c
lab02sort.c
lab03modifysort.c
lab04copyfile.c
lab05.c
lab07.c
lab09.c
lab11.c

Enter command: ls *.c | sort
hello.c
lab01prime.c
lab02sort.c
lab03modifysort.c
lab04copyfile.c
lab05.c
lab07.c
lab09.c
lab11.c

Enter command: quit
Exiting program...

## How It Works

The program aska the user to enter a command. fgets() reads the input.
If the user enters "quit", the program displays a goodbye message and 
ends the program. For all other commands, the program uses popen() to
create a child process and execute the command.The parent process reads 
the output given by the command through the pipe and displays it on the terminal. 
When the command finishes, pclose() is used to close the pipe and wait for the 
child process to terminate. The program will continue to prompt for a command
until the user enters "quit".