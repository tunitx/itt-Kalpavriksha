#include <stdio.h>
#include <stdlib.h>

#define max_size 10000
int  * arr;
int n;

int size(){
    return n;
}

int isEmpty(){
    if(n == 0){
        printf("the queue is empty\n");
        return 1;
    }
    printf("the queue isnt empty.\n");
    return 0;
}

void enqueue(int data){
    arr[n++] = data;
    printf("data enqueued : %d\n", data); 
}

int dequeue(){
    if(n == 0){
        printf("the stack is Empty\n");
        return -1;
    }
    int data = arr[0];
    for(int i =1; i<n; i++){
        arr[i-1] = arr[i];
    }
    n--;
    printf("data dequeued : %d\n", data);
    return data;
}

int peek(){
    if(n == 0) printf("the queue is empty\n");
    printf("the peek is %d\n", arr[0]);
    return arr[0];
}

int main(){
    arr = (int *)malloc(max_size * sizeof(int));
    n = 0;

    isEmpty();
    enqueue(10);
    enqueue(20);
    peek();
    enqueue(30);
    dequeue();
    size();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
}