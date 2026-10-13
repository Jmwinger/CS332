A simple C program that that traverses a file directory and prints
the file hierarchy starting with the directory that is provided 
with the command-line arguement. The program supports five 
command-line options to list all files in the hierarchy and print size,
permisions, and last access. It also lists files based on size and files
based on directory depth.


Requirements

- GCC compiler
## Compile

```bash
gcc -Wall -o hw02 hw02.c
```

## Run

```bash
    ./hw02
    ./hw02 .
    ./hw02 -S
    ./hw02 -s 1024
    ./hw02 -s 1024 -f jpg 1
    ./hw02 -S -f jpg 1 -s 1024
```


Example

Before execution, the program is run on a directory containing files and subdirectories.

Homework
    hw01.c
    hw02.c
    ReadMeHw02.txt
After execution:

./hw02
A directory hierarchy is displayed:

.
    hw01.c
    hw02
    hw02.c
    ReadMeHw02.txt

How It Works
The program uses getopt() to process command line arguments.
The program recursively traverses the file system
using opendir(), readdir(), and closedir().
For each entry discovered, lstat() is used to obtain 
information about the file or directory. 
The -S option displays file size, permissions, and last access time.
The -s option filters files whose size is less than or equal to the specified value.
The -f option filters files whose names contain a specified substring and whose depth 
is less than or equal to the specified depth. When a symbolic link is encountered, 
the program displays the symbolic link name and the file to which the symbolic link points.
Multiple options can be used together. When more than one filter is specified, 
a file must satisfy all filter conditions before it is displayed.
