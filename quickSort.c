#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void stringToArray(char* str, int* arr, int* size) {
    char* token = strtok(str, " ");
    int index = 0;
    while (token != NULL) {
        arr[index++] = atoi(token);
        token = strtok(NULL, " ");
    }
    *size = index;
}

int main() {
    char input[1000];
    int arr[100];
    int size;

    printf("Enter the array elements separated by spaces: ");
    fgets(input, sizeof(input), stdin);

    stringToArray(input, arr, &size);

    quickSort(arr, 0, size - 1);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}