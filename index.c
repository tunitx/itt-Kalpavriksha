// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101
int main() {
    // Write C code here
    int str1[26] = {0};
    int str2[26] = {0};
    char s1[max_size];
    char s2[max_size];
    
    printf("enter the s1 : ");
    scanf("%s", s1);
    while(getchar()!='\n'){}
    
    printf("enter the s2 : ", s2);
    scanf("%s", s2);
    
    for(int i =0; s1[i]!='\0'; i++){
        str1[s1[i] - 'a'] ++;
    }
    for(int  i= 0; s2[i]!='\0'; i++){
        str2[s2[i] - 'a'] ++;
    }
    int invalid = 0;
    for(int i =0; i<26; i++){
        if(str1[i]!=str2[i]){
            invalid = 1;
            break;
        }
    }
    if(invalid)printf("they arent anagram");
    else printf("yes they are anagram");

    return 0;
}