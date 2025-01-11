#include<stdio.h>
#define max_size 101

int is_digit(char c){
    return c >= '0' && c<='9';
}

int helper(char * temp, int size){
    int i =0, num =0;
    if(temp[i] == '0' && size>1)return 0;
    while(temp[i]!='\0'){
        if(!is_digit(temp[i]))return 0;
        num = num*10 + temp[i] - '0';
        if(num > 255) return 0;
        i++;
    }
    return num <=255;
}

int main(){
    char arr[max_size];
    printf("enter the IP: ");
    scanf("%s", arr);
    getchar();
    
    int i =0, invalid = 0, segment = 0;
    while(arr[i]!='\0'){
        char temp[max_size];
        int k =0;
        while(arr[i]!='.' && arr[i]!='\0'){
            temp[k++] = arr[i];
            i++;
        }
        temp[k] = '\0';
        int res = helper(temp, k);
        if(!res){
            invalid = 1;
            break;
        }
        segment ++;
        i++;
    }
    if(invalid || segment !=4)printf("invalid ip");
    else printf("valid ip");
    
    return 0;
}