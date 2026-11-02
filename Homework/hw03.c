/*
Name: Jordan Wingerter
BlazerId: YOUR_BLAZER_ID
Project #: 3

To compile:
make

To run:
./hw3 <directory_name>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

int is_txt_file(const char *filename)
{
    const char *dot = strrchr(filename, '.');

    if (dot == NULL)
        return 0;

    return strcmp(dot, ".txt") == 0;
}

int count_words(const char *filepath)
{
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char word[256];
    int count = 0;

    while (fscanf(file, "%255s", word) == 1)
    {
        count++;
    }

    fclose(file);
    return count;
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char filepath[PATH_MAX];
    int childCount = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    dir = opendir(argv[1]);

    if (dir == NULL)
    {
        fprintf(stderr, "Error: Directory not found.\n");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(filepath, sizeof(filepath),
                 "%s/%s", argv[1], entry->d_name);

        if (stat(filepath, &fileStat) == -1)
        {
            perror("stat failed");
            continue;
        }

        if (!S_ISREG(fileStat.st_mode))
        {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            closedir(dir);
            return EXIT_FAILURE;
        }

        if (pid == 0)
        {
            printf("File: %s | Size: %ld bytes",
                   entry->d_name,
                   (long)fileStat.st_size);

            if (is_txt_file(entry->d_name))
            {
                int words = count_words(filepath);

                if (words >= 0)
                {
                    printf(" | Words: %d", words);
                }
                else
                {
                    printf(" | Words: Unable to read");
                }
            }

            printf("\n");

            exit(EXIT_SUCCESS);
        }

        childCount++;
    }

    closedir(dir);

    if (childCount == 0)
    {
        printf("No files found in directory.\n");
    }

    for (int i = 0; i < childCount; i++)
    {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}