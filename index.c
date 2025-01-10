#include<stdio.h>

int main(){
    char arr[100];
    printf("enter the string: ");
    scanf("%s", arr);
    
    int chars[26] = {0};
    char op[100];
    
    int i =0, j =0;
    while(arr[i]!='\0'){
        if(chars[(int)(arr[i] - 'a')]){
            i++;
            continue;
        }
        else{
            chars[(int)(char)(arr[i] - 'a')] = 1;
            op[j] = arr[i];
            i++;
            j++;
        }
    }
    op[j] = '\0';
    
    printf("ther op is : %s", op);
}