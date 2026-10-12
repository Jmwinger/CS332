#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int given_number;
    int count = 0;

    if (argc != 2)
    {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    given_number = atoi(argv[1]);

    if (given_number <= 1)
    {
        printf("%d is not prime\n", given_number);
    }
    else
    {
        for (int i = 1; i <= given_number; i++)
        {
            if (given_number % i == 0)
                count++;
        }

        if (count == 2)
            printf("%d is prime\n", given_number);
        else
            printf("%d is not prime\n", given_number);
    }

    return 0;
}