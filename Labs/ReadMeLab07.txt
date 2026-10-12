# Process Management

A simple C program that reads commands from an input
file and creates child processes using fork(). It xecutes
commands using execvp(), uses wait() to wait for the child 
process to finish, and records execution times in a log file.

## Requirements

- GCC compiler
## Compile

```bash
gcc -Wall -o lab07 lab07.c
```

## Run

```bash
./lab07 commands.txt
cat output.log
```

## Example

Before execution, the commands.txt file contains commands
to be executed:
uname -a 
./lab01prime 500
./lab01prime 1000
```
After execution: 
A few tile output.log is created: 

uname -a   Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202
date    Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202
ls -1   Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202
./lab01prime 100        Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202
./lab01prime 500        Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202
./lab01prime 1000       Mon Oct 12 03:15:35 202 Mon Oct 12 03:15:35 202

```

## How It Works

The program opens an input file and reads one command at a time using fgets().
For each command, the parent process records the start 
time and then creates a child process using fork().
The child process executes the command using execvp() 
while the parent process waits for completion using waitpid().
After the child process terminates, the parent process
records the end time and writes the command, start time, 
and end time to output.log using fprintf(). 
Timestamps are generated using ctime().

