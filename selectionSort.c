#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    char input[1000];
    printf("Enter the array elements separated by spaces: ");
    fgets(input, 1000, stdin);

    int arr[100], n = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    selectionSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}