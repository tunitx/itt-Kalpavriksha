#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max_size 1000
int * stack;
int top;

int isEmpty(){
    if(top == 0) return 1;
    return 0;
}

int size(){
    printf("the size is : %d\n", top);
    return top;
}

int peek(){
    if(!isEmpty()){
         printf("Element at peek : %d\n", stack[top-1]);
        return stack[top-1];
    } 
    printf("stack is Empty\n");
    return INT_MAX;
}

int push(int data){
    if(top == max_size){
        printf("stack size is full\n");
        return 0;
    } 
    stack[top] = data;
    top++;

}

int pop(){
    if(isEmpty()){
        printf("stack is Empty\n");
        return 0;
    }

    top--;
    printf("Element popped : %d\n", stack[top]);
    return stack[top];

}

int main (){
    stack = (int *)malloc(max_size * sizeof(int));
    top = 0;

   push(10);
   push(12);
   push(13);
   pop();
   peek();
   size();
   pop();
   pop();
   pop();
   pop();
   
}