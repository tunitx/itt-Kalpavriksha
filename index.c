// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 1000
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
void helper(char * str, int * chars, char * curr_str, char ** ans, int size, int  curr_str_index, int * ans_index){
    if(curr_str_index == size ){
        curr_str[curr_str_index] = '\0';
       strcpy(ans[*ans_index], curr_str);
        (*ans_index)++ ;
        return;
    }
    
    for(int i =0; str[i]!='\0'; i++){
        if(chars[str[i] - 'a'] !=0)continue;
        
        curr_str[curr_str_index] = str[i];
        chars[str[i] - 'a'] = 1;
        helper(str, chars, curr_str, ans, size, curr_str_index+1, ans_index);
        chars[str[i] - 'a'] = 0;
    }
}

int main() {
    // Write C code here
    int chars[26]= {0};
    char str[max_size];
    printf("enter the string : ");
    scanf("%s", str);
    getchar();
    int size = 0;
    for(; str[size]!='\0'; size ++){
    }
    int permutations = factorial(size);
    
    char **ans = (char **)malloc(permutations * sizeof(char *));
    for(int i =0; i<permutations; i++){
        ans[i] = (char* )malloc((size + 1) * sizeof(char));
    }
    
    char curr_str[max_size];
    int curr_str_index = 0, ans_index = 0;
    helper(str, chars, curr_str, ans, size, curr_str_index, &ans_index);
     printf("Permutations:\n");
    for (int i = 0; i < ans_index; i++) {
        printf("%s\n", ans[i]);
        free(ans[i]);  
    }
    free(ans);
    return 0;
}ad