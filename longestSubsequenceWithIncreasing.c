#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


int longestConsecutiveSubsequence(int arr[], int n) {
    if (n == 0) return 0;

    bubbleSort(arr, n); 

    int longest = 1, current = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1] + 1) { 
            current++;
        } else if (arr[i] != arr[i - 1]) { 
            longest = (current > longest) ? current : longest;
            current = 1;
        }
    }
    

    if (current > longest) longest = current;
    
    return longest;
}

int main() {
    int arr[] = {100, 4, 200, 1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = longestConsecutiveSubsequence(arr, n);
    printf("Length of longest consecutive subsequence: %d\n", result);
    
    return 0;
}
