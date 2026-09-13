#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readStrings(char **arr, int size);
void sortStrings(char **arr, int size);
void displayStrings(char **arr, int size);

int main() {
    int N;

    printf("Enter number of strings: ");
    scanf("%d", &N);

    char **arr = (char **)malloc(N * sizeof(char *));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    readStrings(arr, N);

    printf("\nOriginal Strings:\n");
    displayStrings(arr, N);

    sortStrings(arr, N);

    printf("\nSorted Strings:\n");
    displayStrings(arr, N);

    /* Free allocated memory */
    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void readStrings(char **arr, int size) {
    char temp[100];

    for (int i = 0; i < size; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%99s", temp);

        arr[i] = (char *)malloc((strlen(temp) + 1) * sizeof(char));

        if (arr[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        strcpy(arr[i], temp);
    }
}

void displayStrings(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

void sortStrings(char **arr, int size) {
    for (int i = 1; i < size; i++) {
        char *key = arr[i];
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}