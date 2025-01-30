#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    char input[256];
    printf("Enter sorted array elements separated by spaces: ");
    fgets(input, 256, stdin);

    char *token = strtok(input, " ");
    int arr[256], size = 0;

    while (token != NULL) {
        arr[size++] = atoi(token);
        token = strtok(NULL, " ");
    }

    int target;
    printf("Enter the element to search: ");
    scanf("%d", &target);

    int result = binarySearch(arr, size, target);
    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    return 0;
}