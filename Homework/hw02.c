/*
 * Name: James Winger
 * BlazerId:
 * Project #: HW2
 *
 * To Compile:
 * gcc -Wall -o search search.c
 *
 * To Run:
 * ./search
 * ./search directory
 * ./search -S
 * ./search -s 1024
 * ./search -f jpg 1
 * ./search -S -s 1024 -f jpg 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>

int showAttributes = 0;
long maxSize = -1;
char *pattern = NULL;
int maxDepth = -1;

void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("\t");
}

void print_permissions(mode_t mode)
{
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');

    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');

    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

int matches_filters(const char *name,
                    const struct stat *sb,
                    int depth)
{
    if (maxSize >= 0 &&
        S_ISREG(sb->st_mode) &&
        sb->st_size > maxSize)
    {
        return 0;
    }

    if (pattern != NULL)
    {
        if (strstr(name, pattern) == NULL)
            return 0;

        if (depth > maxDepth)
            return 0;
    }

    return 1;
}

void print_entry(const char *name,
                 const struct stat *sb,
                 int depth)
{
    if (!matches_filters(name, sb, depth))
        return;

    print_indent(depth);
    printf("%s", name);

    if (showAttributes)
    {
        printf(" (");

        if (S_ISDIR(sb->st_mode))
            printf("0 ");
        else
            printf("%ld ", (long)sb->st_size);

        print_permissions(sb->st_mode);

        char *t = ctime(&sb->st_atime);

        if (t != NULL)
        {
            t[strlen(t) - 1] = '\0';
            printf(" %s", t);
        }

        printf(")");
    }

    printf("\n");
}

void traverse(const char *path, int depth)
{
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    char fullpath[PATH_MAX];

    dir = opendir(path);

    if (dir == NULL)
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(fullpath,
                 sizeof(fullpath),
                 "%s/%s",
                 path,
                 entry->d_name);

        if (lstat(fullpath, &sb) < 0)
            continue;

        if (S_ISLNK(sb.st_mode))
        {
            char target[PATH_MAX];

            ssize_t len =
                readlink(fullpath, target,
                         sizeof(target) - 1);

            if (len >= 0)
            {
                target[len] = '\0';

                print_indent(depth + 1);
                printf("%s (%s)\n",
                       entry->d_name,
                       target);
            }

            continue;
        }

        print_entry(entry->d_name,
                    &sb,
                    depth + 1);

        if (S_ISDIR(sb.st_mode))
        {
            traverse(fullpath, depth + 1);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    int opt;
    char *startDir = ".";

    while ((opt = getopt(argc,
                         argv,
                         "Ss:f:")) != -1)
    {
        switch (opt)
        {
        case 'S':
            showAttributes = 1;
            break;

        case 's':
            maxSize = atol(optarg);
            break;

        case 'f':
            pattern = optarg;

            if (optind < argc)
            {
                maxDepth = atoi(argv[optind]);
                optind++;
            }
            else
            {
                fprintf(stderr,
                        "-f requires pattern and depth\n");
                exit(EXIT_FAILURE);
            }

            break;

        default:
            fprintf(stderr,
                    "Usage: ./search [-S] [-s size] "
                    "[-f pattern depth] [directory]\n");
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc)
        startDir = argv[optind];

    printf("%s\n", startDir);

    traverse(startDir, 0);

    return 0;
}