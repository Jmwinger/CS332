/*
 * lab07.c
 *
 * Reads commands from an input file.
 * Creates a child process using fork().
 * Executes commands using execvp().
 * Parent waits for child and logs execution times.
 *
 * Compile:
 * gcc -Wall -o lab07 lab07.c
 *
 * Run:
 * ./lab07 commands.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main(int argc, char *argv[])
{
    FILE *inputFile;
    FILE *logFile;
    char line[MAX_LINE];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s inputfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    inputFile = fopen(argv[1], "r");

    if (inputFile == NULL)
    {
        perror("fopen input file");
        return EXIT_FAILURE;
    }

    logFile = fopen("output.log", "w");

    if (logFile == NULL)
    {
        perror("fopen output.log");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        char originalLine[MAX_LINE];

        strcpy(originalLine, line);

        originalLine[strcspn(originalLine, "\n")] = '\0';
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
            continue;

        char *args[MAX_ARGS];
        int argCount = 0;

        char *token = strtok(line, " ");

        while (token != NULL && argCount < MAX_ARGS - 1)
        {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }

        args[argCount] = NULL;

        time_t startTime = time(NULL);

        pid_t pid = fork();

        if (pid == 0)
        {
            execvp(args[0], args);

            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            int status;

            waitpid(pid, &status, 0);

            time_t endTime = time(NULL);

            if (WIFEXITED(status))
            {
                char *startStr = ctime(&startTime);
                char *endStr = ctime(&endTime);

                startStr[strlen(startStr) - 1] = '\0';
                endStr[strlen(endStr) - 1] = '\0';

                fprintf(logFile,
                        "%s\t%s\t%s\n",
                        originalLine,
                        startStr,
                        endStr);

                fflush(logFile);
            }
        }
        else
        {
            perror("fork");
        }
    }

    fclose(inputFile);
    fclose(logFile);

    printf("Execution complete. Check output.log\n");

    return EXIT_SUCCESS;
}
                   