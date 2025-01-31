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
    Stack * stack;
} Queue;

Queue * createQueue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->stack = createStack();
    return q;
}

int isQueueEmpty(Queue * q){
    return isStackEmpty(q->stack);
}

int queueSize(Queue * q){
    return stackSize(q->stack);
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

int peekQueue(Queue * q){
    if(isQueueEmpty(q)) return 0;
    return peekQueueHelper(q->stack);
}

void enqueue(Queue * q, int data){
    push(q->stack, data);
}

int dequeueHelper(Stack * stack){
    if(stack->top->next == NULL){
        int data = pop(stack);
        return data;
    }

    int topVal = pop(stack);
    int returnVal = dequeueHelper(stack);

    push(stack, topVal);
    return returnVal;
}

int dequeue(Queue * q){
    if(isStackEmpty(q->stack)) return 0;

    return dequeueHelper(q->stack);
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