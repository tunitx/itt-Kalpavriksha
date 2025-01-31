#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode  = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

typedef struct Stack{
    Node * top;
    int size;
} Stack;

Stack * createStack(){
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

int stackSize(Stack * stack){
    return stack->size;
}

int isStackEmpty(Stack * stack){
    return (stack->top == NULL) ? 1 : 0;
}

void push(Stack * stack,  int data){
    // if(stack->top == NULL) return 0;

    Node * newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size ++;

}

int pop(Stack * stack){
    if(isStackEmpty(stack)) return 0;

    Node * freeNode = stack->top;
    stack->top = stack->top->next;
    stack->size --;

    int data = freeNode->data;
    free(freeNode);

    return data;
    
}

int peekStack(Stack * stack){
    if(isStackEmpty(stack)) return 0;

    return stack->top->data;
}

typedef struct Queue{
    Stack * stack1;
    Stack * stack2;
} Queue;

Queue * createQueue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->stack1 = createStack();
    q->stack2 = createStack();
    return q;
}

int isQueueEmpty(Queue * q){
    return isStackEmpty(q->stack1);
}

int queueSize(Queue * q){
    return stackSize(q->stack1);
}

int peekQueueHelper(Stack * stack){
    if(stack->top->next == NULL){
        return peekStack(stack);
    }

    int topVal = pop(stack);
    int returnVal = peekQueueHelper(stack);

    push(stack, topVal);
    return returnVal;
}

int peekQueue(Queue *q) {
    if (isQueueEmpty(q)) return -1;

    while (!isStackEmpty(q->stack1)) {
        push(q->stack2, pop(q->stack1));
    }

    int front = peekStack(q->stack2); 

    while (!isStackEmpty(q->stack2)) {
        push(q->stack1, pop(q->stack2));
    }

    return front;
}
void enqueue(Queue * q, int data){
    push(q->stack1, data);
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) return -1; 

    while (!isStackEmpty(q->stack1)) {
        push(q->stack2, pop(q->stack1));
    }

    int data = pop(q->stack2); 

    while (!isStackEmpty(q->stack2)) {
        push(q->stack1, pop(q->stack2));
    }

    return data;
}


int main(){
    Queue * q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    
    printf("Front: %d\n", peekQueue(q));  
    
    printf("Dequeued: %d\n", dequeue(q));  
    printf("Dequeued: %d\n", dequeue(q));  
    
    printf("Front: %d\n", peekQueue(q));  
    
}