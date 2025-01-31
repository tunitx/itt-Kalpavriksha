#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node *front, *rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {  
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;  
    q->rear = newNode;        
}

int dequeue(Queue* q) {
    if (q->front == NULL) {  
        printf("Queue is empty\n");
        return -1;
    }

    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)  
        q->rear = NULL;

    free(temp);
    return value;
}


int front(Queue* q) {
    return (q->front) ? q->front->data : -1;
}


int isEmpty(Queue* q) {
    return q->front == NULL;
}

void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}


int main() {
    Queue* q = createQueue();
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    
    printf("Front: %d\n", front(q));  
    
    printf("Dequeued: %d\n", dequeue(q));  
    printf("Dequeued: %d\n", dequeue(q));  
    
    printf("Front: %d\n", front(q));  
    
    freeQueue(q);
    return 0;
}
