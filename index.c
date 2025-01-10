// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101
int helper(char *temp, int i, char * s1){
    int j =0;
    while(temp[i]!= '\0' && s1[j]!= '\0'){
        if(temp[i]!=s1[j]) return 0;
        j++;
        i++;
    }
    return (s1[j] == '\0');
}
int main() {
    // Write C code here
    char s1[max_size];
    char s2[max_size];
    
    printf("enter the s1: ");
    scanf("%s", s1);
    
    getchar();
    
    printf("enter the s2: ");
    scanf("%s", s2);
    getchar();
    
    int len1 =0, len2 =0;
    for(int i =0; s1[i]!='\0'; i++){
        len1 ++;
    }
    for(int i =0; s2[i]!='\0'; i++){
        len2 ++;
    }
    
    if(len1!=len2){
        printf("false");
        return 0;
    }
    char temp [len1 + len2 + 1];
    int j =0;
    for(int i =0; s2[i]!='\0'; i++){
        temp[j++] = s2[i]; 
    }
    for(int i =0; s2[i]!='\0'; i++){
        temp[j++] = s2[i];
    }
    temp[j] = '\0';
    
    for(int i =0; temp[i]!='\0'; i++){
        if(helper(temp, i, s1)){
            printf("true");
            return 0;
        } 
    }
    printf("false");
    return 0;
}