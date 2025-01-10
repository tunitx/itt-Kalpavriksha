// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101


int main() {
   char arr[max_size];
   printf("enter the string: ");
   fgets(arr, max_size, stdin);
//   while(getchar()!= '\n');
   
   int end = 0;
   for(int i =0; i<max_size; i++){
       if(arr[i] == '\n'){
           arr[i] = '\0';
           end = i;
           break;
       }
   }
   end -- ;
while(arr[end] ==' ' )end --;
   int count  =0, i =0;
   while(arr[i] == ' ')i++;
   
   while(i<=end){
     if (arr[i] != ' ' && (i == end || arr[i + 1] == ' ')) {
            count++;
        }
        i++;
   }
   printf("the number of words is: %d", count);

    return 0;
}