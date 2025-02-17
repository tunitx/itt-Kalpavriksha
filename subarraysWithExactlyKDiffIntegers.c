#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define max_size 100001
#define OFFSET 10000

int helper(int * arr, int k, int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        int map[20001] = {0}; 
      
        int distinct = 0;
        
        for(int j = i; j < n; j++){
            if (map[arr[j] + OFFSET] == 0) 
                distinct++;
            map[arr[j] + OFFSET]++;

            if (distinct == k)
                count++;
            else if (distinct > k) break;
        }
    }
    return count;
}

void parseInput(int * arr, int * k, int *n){
    
    char input[max_size];
    fgets(input, max_size, stdin);
    input[strcspn(input, "\n")] = '\0';
    scanf("%d", k);

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

int main(){
    int arr[max_size];
    int k, n;
    parseInput(arr, &k, &n);

    int count = helper(arr, k, n);
    printf("the count is %d", count);
}