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
    Queue * q1;
    Queue * q2;
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

int stackSize(Stack * stack){
    return queueSize(stack->q1);
}

int isStackEmpty(Stack * stack){
    return isQueueEmpty(stack->q1);
}

void push(Stack * stack, int data){
    enqueue(stack->q1, data);
}

int peekStack(Stack * stack){
    if(isStackEmpty(stack)) return 0;

     while(stack->q1->front->next!=NULL){
        enqueue(stack->q2, dequeue(stack->q1));
    }
    int data = peekQueue(stack->q1);
    enqueue(stack->q2, dequeue(stack->q1));

    Queue * temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
    return data;
    
}

int pop(Stack * stack){
    if(isStackEmpty(stack)) return 0;

    while(stack->q1->front->next!=NULL){
        enqueue(stack->q2, dequeue(stack->q1));
    }

    int data = dequeue(stack->q1);
    Queue * temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
    stack->q1->size --;
    return data;
}


Queue * createQueue(){
    Queue  * q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

Stack * createStack(){
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->q1 = createQueue();
    stack->q2 = createQueue();

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