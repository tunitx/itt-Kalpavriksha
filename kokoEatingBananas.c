#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int maxPile = 0;
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }

    int left = 1, right = maxPile;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int hours = 0;
        for (int i = 0; i < pilesSize; i++) {
            hours += (piles[i] + mid - 1) / mid; 
        }
        if (hours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int* parseInput(char* str, int* size) {
    int* arr = (int*)malloc(10000 * sizeof(int)); 
    int count = 0;
    char* token = strtok(str, ",");
    while (token != NULL) {
        arr[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    *size = count;
    return arr;
}

int main() {
    char input[] = "30,11,23,4,20";
    int h = 6;

    int size;
    int* piles = parseInput(input, &size);

    int result = minEatingSpeed(piles, size, h);
    printf("Minimum eating speed: %d\n", result);

    free(piles); 
    return 0;
}