// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101

int is_digit(char c){
return (c >= '0' && c <= '9');
}

int main() {
    // Write C code here
    char arr[max_size];
    printf("enter the string: ");
    fgets(arr, max_size, stdin);
    
    int end = 0;
    for(; arr[end]!='\n'; end ++){
        
    }
    
    
    arr[end] = '\0';
    end --;
   while(end >=0 && arr[end] == ' '){
       end --;
   }
   int start =0;
   while(start <= end && arr[start] == ' '){
       start ++;
   }
   if(start > end){
       printf("invalid input");
       return 0;
   }
   int ans = 0, invalid = 0, neg = 1;
   if(arr[start] == '-'){
        neg = -1;
        start ++;
   }
   else if(arr[start] == '+') start ++;
   while(start <= end){
       if(!is_digit(arr[start])){
           invalid = 1;
           break;
       }
       else{
           ans = ans*10 + (arr[start] - '0');
           start ++;
       }
   }
  if (invalid) {
        printf("Invalid input");
    } else {
        printf("The number is: %d", ans * neg);
    }
    

    return 0;
}