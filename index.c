// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101

int check(int start, int end, char * arr){
    while(start < end){
        if(arr[start]!=arr[end]) return 0;
        start ++;
        end--;
    }
    return 1;
}

int main() {
    // Write C code here
    char arr[max_size];
    printf("enter the string: ");
    scanf("%s", arr);
    getchar();
    
    int max_start = 0, max_len = 0;
    for(int i =0; arr[i]!='\0'; i++){
        for(int j = i; arr[j]!='\0'; j++){
            int res = check(i, j, arr);
            if(res){
                if(j-i+1 > max_len){
                    max_len = j-i+1;
                    max_start = i;
                }
            }
        }
    }
    
    char temp [max_size];
    for(int i = 0; i<max_len; i++){
        temp[i] = arr[i+max_start];
    }
    temp[max_len] = '\0';
    printf("the longest pallindromic substring is : %s", temp);

    return 0;
}