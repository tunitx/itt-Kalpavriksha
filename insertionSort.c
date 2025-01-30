#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    char input[256];
    printf("Enter the array elements separated by spaces: ");
    fgets(input, 256, stdin);

    int arr[100];
    int n = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    insertionSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}