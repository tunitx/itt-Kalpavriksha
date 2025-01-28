#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    char input[100];
    printf("Enter the array elements separated by spaces: ");
    fgets(input, sizeof(input), stdin);

    int arr[100];
    int n = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    bubbleSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}