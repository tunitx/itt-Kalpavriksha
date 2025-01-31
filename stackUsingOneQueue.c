#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

typedef struct Queue{
    Node * front;
    Node * rear;
    int size;
} Queue;

typedef struct Stack{
    Queue * q;
} Stack;

Node * createNode(int data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue * q, int data){
    Node * newNode = createNode(data);

    if(q->rear == NULL){
        q->front = newNode;
        q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size ++;
}

int dequeue(Queue * q){
    if(q->front == NULL) {
        printf("Stack is Empty");
        return 0;
    }

    int data = q->front->data;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    q->size --;

    return data;
}

int queueSize(Queue * q){
    return q->size;
}

int isQueueEmpty(Queue * q){
    return q->front == NULL ? 1 : 0;
}

int peekQueue(Queue * q){
    if(q->front != NULL) return q->front->data;
    return 0;
}



int isStackEmpty(Stack * stack){
    int data =isQueueEmpty(stack->q);
    if(data == 1) printf("yes stack is Empty\n");
    else printf("No stack isnt empty\n");

    return data;
}

int peekStack(Stack * stack){
    int data = peekQueue(stack->q);
    if(data == 0){
        printf("the stack is Empty\n");
        return 0;
    }
    printf("the peek of the stack is %d\n", data);
    return data;
}

void push(Stack * stack, int data){
    enqueue(stack->q, data);
    int size = stack->q->size -1;
    while(size > 0){
        enqueue(stack->q, dequeue(stack->q));
        size --;
    }
}

int pop(Stack * stack){
    return dequeue(stack->q);
}

int stackSize(Stack * stack){
    return stack->q->size;
}

Queue * createQueue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

Stack * createStack(){
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->q = createQueue();
    return stack;
}


int main(){
    Stack * stack = createStack();
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Top: %d\n", peekStack(stack));  

    printf("Popped: %d\n", pop(stack));  
    printf("Popped: %d\n", pop(stack));  

    printf("Top: %d\n", peekStack(stack));  

    
}
