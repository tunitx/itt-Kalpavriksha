// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101
int main() {

    char str[max_size];
    char char_to_replace;
    
    printf("enter the string; ");
    fgets(str, max_size, stdin);
    int end = 0;
    for(; str[end]!='\n'; end ++){
    }
    str[end] = '\0';
    
    printf("enter the character to replace: ");
    scanf("%c", &char_to_replace);
    
    int char_map[256] = {0};
    
    for(int i =0; str[i]!='\0'; i++){
        if(str[i] == ' ')continue;
      char_map[str[i]]++;
    }
    for(int i =0; str[i]!='\0'; i++){
        if(char_map[str[i]] == 1){
            str[i] = char_to_replace;
            break;
        }
    }
    
    printf("the modified string is: %s", str);
    return 0;
}