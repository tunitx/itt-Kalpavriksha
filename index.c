// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#define max_size 101

int helper(char *arr,int i, char *sub){
    int j =0;
    while(arr[i]!= '\0' && sub[j]!='\0'){
        if(arr[i]!=sub[j]) return 0;
        i++;
        j++;
    }
    return (sub[j] == '\0');
    
}

int main() {
   char arr[max_size];
   char sub[max_size];
   printf("enter the string : ");
   fgets(arr, max_size, stdin);
   arr[strcspn(arr, "\n")] = '\0';
   
   printf("enter the substring: ");
   scanf("%s", sub);
   
   int ans =0, not_found = 0;
   for(int i =0; arr[i]!='\0'; i++){
       if(helper(arr, i , sub)){
           not_found = 1;
           ans = i;
           break;
       }
   }
   if(not_found == 0) printf("not found");
   else  printf("the ans is : %d", ans);
    return 0;
}