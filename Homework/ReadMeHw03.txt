A simple C program that accepts a directory as a command-
line argument and creates a child process for each
file found in the directory. Each child process prints the
file name, file size, and the number of words in the file.



Requirements

- GCC compiler
## Compile

```bash
gcc -Wall -Wextra -o hw03 hw03.c
```

## Run

```bash
    ./hw03 .
    ./hw03 testdir
    ./hw03 Homework
```


Example

Before execution, 

Homework
     hw02.c    
     ReadMeHw03.txt 
     hw01.c 
     hw03 
     hw03.c 
     Makefile
     hw02 
After execution:

./hw03 . 
   hw02.c | Size: 4023 bytes
   File: ReadMeHw03.txt | Size: 798 bytes | Words: 122
   File: hw01.c | Size: 1 bytes
   File: ReadMeHw02.txt | Size: 1673 bytes | Words: 263
   File: hw03 | Size: 16888 bytes
   File: hw03.c | Size: 2608 bytes
   File: Makefile | Size: 118 bytes
   File: hw02 

After execution,

./hw03 testdir
   File: file2.txt | Size: 15 bytes | Words: 4
   File: file1.txt | Size: 12 bytes | Words: 2

After execution,

./hw03 Homework
   Error: Directory not found.

How It Works
The program uses fork() to create a child process which prints the
file name, size (in bytes), and count and print the number 
of words in the file.The parent process waits for all child processes to complete
using wait() before terminating. stat() is used to obtain information about each file,
including its size in bytes. 

Edge Cases Handled

- Invalid command-line arguments.
- Directory does not exist.
- Empty directories.
- Directories containing no regular files.
- Files that cannot be opened.
- Empty text files.
- Failed fork() calls.