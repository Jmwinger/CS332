#include <stdio.h>

int main (){
    int arr[3];

    printf ("Enter three integers: ");
    scanf ("%d %d %d", &arr[0], &arr[1], &arr[2]);

    printf ("Given elements are: [%d, %d, %d]\n", arr[0], arr[1], arr[2]);


    for (int i = 1; i < 3; i++){
        int currLoc = i;
        while (currLoc > 0 && arr[currLoc - 1] > arr[currLoc]){
            int temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;
            currLoc--;
        }
    }

    printf ("Sorted array: [%d, %d, %d]\n", arr[0], arr[1], arr[2]);

    return 0;
}
