#include <stdio.h>
#define max_size 101

int main() {
    char arr[max_size];
    printf("Enter the sentence: ");
    fgets(arr, max_size, stdin);
    int end = 0;
    while (arr[end] != '\n' && arr[end] != '\0') {
        end++;
    }
    arr[end--] = '\0';
    while (end >= 0 && arr[end] == ' ') {
        end--;
    }
    int start = 0;
    while (start <= end && arr[start] == ' ') {
        start++;
    }

    if (start > end) {
        printf("No words found.\n");
        return 0;
    }

    int max_len = 0, curr_len = 0;
    int start_index = start, max_start = start;

    for (int i = start; i <= end; i++) {
        if (arr[i] != ' ') {
            curr_len++;
        } else {
            if (curr_len > max_len) {
                max_len = curr_len;
                max_start = i - curr_len;
            }
            curr_len = 0;
        }
    }

    
    if (curr_len > max_len) {
        max_len = curr_len;
        max_start = end - curr_len + 1;
    }
    char ans[max_len + 1];
    for (int i = 0; i < max_len; i++) {
        ans[i] = arr[max_start + i];
    }
    ans[max_len] = '\0';

    printf("Longest word is: %s\n", ans);
    return 0;
}
