// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101

int main() {
    // Write C code here
    char arr[max_size];
    char c;
    printf("enter the sentence: ");
    fgets(arr, max_size, stdin);
    printf("enter the character: ");
    scanf("%c", &c);
    
    int start = 0, end = 0;
    for(; arr[end]!='\n'; end ++){
        
    }
    end --;
    for(; arr[end] == ' '; end--){
        
    }
    
    for(; arr[start] == ' '; start ++){
        
    }
    
    char ans [max_size];
    int j = 0;
    for(int i = start; i<=end; i ++){
        if(arr[i] == c)continue;
        else{
            ans[j++] = arr[i];
        }
    }
    ans[j] = '\0';
    
    printf("ans is : %s", ans);
    

    return 0;
}