/*
 * Modified forkexecvp.c
 * Ctrl-C  -> sends SIGINT to child
 * Ctrl-Z  -> sends SIGTSTP to child
 * Ctrl-\  -> terminates parent
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid = -1;

void signal_handler(int signo){
    switch(signo)    {
        case SIGINT:
            printf("\nParent caught SIGINT\n");
            if (child_pid > 0)
                kill(child_pid, SIGINT);
            break;

        case SIGTSTP:
            printf("\nParent caught SIGTSTP\n");
            if (child_pid > 0)
                kill(child_pid, SIGTSTP);
            break;

        case SIGQUIT:
            printf("\nParent caught SIGQUIT\n");
            printf("Exiting parent process...\n");

            if (child_pid > 0)
                kill(child_pid, SIGTERM);

            exit(0);
    }
}

int main(int argc, char **argv){
    int status;

    if (argc < 2)    {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGQUIT, signal_handler);

    child_pid = fork();

    if (child_pid == 0)    {
        execvp(argv[1], &argv[1]);

        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0)    {
        printf("Parent PID = %ld\n", (long)getpid());
        printf("Child PID  = %ld\n", (long)child_pid);
        printf("Press Ctrl-C, Ctrl-Z, or Ctrl-\\\n");

        while (1)        {
            pause();

            if (waitpid(child_pid, &status, WNOHANG) > 0)            {
                if (WIFEXITED(status))                {
                    printf("Child exited with status %d\n",
                           WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status))                {
                    printf("Child terminated by signal %d\n",
                           WTERMSIG(status));
                }
            }
        }
    }else{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}