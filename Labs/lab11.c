/*
 * lab11.c
 *
 * Prompts the user for UNIX commands, executes them using
 * popen(), displays the output, and repeats until "quit"
 * is entered.
 *
 * Compile: gcc -Wall -Wextra lab11.c -o lab11
 * Run: ./lab11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char command[1024];
    char buffer[BUFSIZ];
    FILE *fp;

    while (1) {
        printf("Enter command: ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Check for quit command */
        if (strcmp(command, "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }

        /* Skip empty commands */
        if (strlen(command) == 0) {
            continue;
        }

        fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            continue;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        if (pclose(fp) == -1) {
            perror("pclose");
        }
    }

    return 0;
}