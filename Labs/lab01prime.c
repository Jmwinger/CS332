#include <stdio.h>

int main() {
    int given_number;
    int count = 0;

    printf("Enter a number: ");
    scanf("%d", &given_number);

    if (given_number <= 1) {
        printf("%d is not prime\n", given_number);
    }
    else {
        for (int i = 1; i <= given_number; i++) {
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