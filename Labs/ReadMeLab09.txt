# Signal Handling

A simple C program that demonstrates UNIX signal handling
using fork(), execvp(), signal(), and kill(). The program
creates a child process that executes a command while the
parent process handles user inputted keyboard signals.

## Requirements

- GCC compiler

## Compile

```bash
gcc -Wall -o lab09 lab09.c


Example

Before execution:

./lab09 sleep 100

During execution:

Parent PID = 5647
Child PID  = 5648

Ctrl-C
Parent caught SIGINT

Ctrl-Z
Parent caught SIGTSTP

Ctrl-\
Parent caught SIGQUIT
Exiting parent process...

Signals

Ctrl-C (SIGINT) interrupts the child process.
Ctrl-Z (SIGTSTP) stops the child process.
Ctrl-\ (SIGQUIT) terminates the parent process.
The parent continues running until SIGQUIT (Ctrl-\) is received.

## How It Works

The program starts by utilizing fork() to create the child process by cloning
the parent process. The child process executes a command given when the user 
types input through the command line using execvp(). Once a signal is called, 
either SIGINT, SIGTSTP, or SIGQUIT, an action is performed. Either the default 
action, ignoring the signal, or catching and handling. When the user presses 
Ctrl-C, the parent catches SIGINT and sends the signal to the child process 
using kill(). When the user presses Ctrl-Z, the parent catches SIGTSTP to stop
the child process. When the user presses Ctrl-/, the parent catches SIGQUIT, 
kills the child process if necessary, and exits the program. The parent 
uses pause() to wait for signals and respond to them.