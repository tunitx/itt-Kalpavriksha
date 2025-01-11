// Online C compiler to run C program online
#include <stdio.h>
#define max_size 101

int main() {
    // Write C code here
    char arr[max_size];
    printf("enter the string : ");
    scanf("%s", arr);
    getchar();
    
    int size = 0;
    char ans[max_size];
    for(int i =0; arr[i]!='\0'; i++){
        char curr_char = arr[i];
        int j = i, curr_len = 0;
        
        while(arr[j] == curr_char && arr[j]!='\0'){
            j++;
            curr_len ++;
        }
        int temp [max_size];
        int k =0;
        while(curr_len > 0){
            temp[k++] = curr_len%10;
            curr_len = curr_len/10;
        }
        k--;
        ans[size ++] = curr_char;
        while(k>=0){
            ans[size++] = temp[k--] + '0';
        }
        // ans[size++] = curr_char;
        // ans[size++] = curr_len + '0';
        
        i = j-1;
    }
    ans[size] = '\0';
    int arr_size =0;
    for(int i =0; arr[i]!='\0'; i++){
        arr_size ++;
    }
    arr_size ++;
    
    if(size > arr_size)printf("the ans is : %s", arr);
    else printf("the ans is : %s", ans);

    return 0;
}