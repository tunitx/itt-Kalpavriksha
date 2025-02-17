#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define max_size 100001

void parseInput(int * arr,  int *n){
    
    char input[max_size];
    fgets(input, max_size, stdin);
    input[strcspn(input, "\n")] = '\0';

    int index = 0;
    int neg = 0;
    for(int i =0; input[i] !='\0'; i++){
        if(input[i] == '-'){
            neg = 1;
            continue;
        } 
       if(isdigit(input[i])){
            int j = i;
            int m=0;
            char temp[max_size];
            while(input[j]!='\0' && isdigit(input[j]) ){
                temp[m] = input[j];
                m++;
                j++;
            }
            temp[m] = '\0';
            int num = atoi(temp);
            if(neg) num *= -1;
            neg = 0;
            arr[index ++ ] = num;

            i = j-1;
       }
    }
    *n = index;

    printf("the array is : ");
    for(int i =0; i<*n; i++){
        printf("%d,", arr[i]);
    }
}

int helper(int * nums, int n ){
    int count = 0;
    for(int i =1; i<n; i++){
        if(nums[i] <= nums[i-1]){
            int x = nums[i-1] - nums[i] + 1;
            count += x;
            nums[i] = nums[i-1] + 1;
        }
    }
    return count;
}

int main(){
    int arr[max_size];
    int  n;
    parseInput(arr, &n);

    printf("the min ops are : %d\n", helper(arr,n));
}