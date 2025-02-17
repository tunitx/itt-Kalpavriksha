#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char * task;
    struct Node * next;
} Node;

Node * createNode(char * task){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->task = strdup(task);

    return newNode;
}

typedef struct Queue{
    Node * front, *rear;
} Queue;

Queue * createQueue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->rear = NULL;
    q->front = NULL;

    return q;
}

void enqueue(Queue * q, char * task){
    Node * newNode = createNode(task);
    if(q->front == NULL){
        q->front = newNode;
        q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return;
}

int dequeue(Queue * q, char * task){
    if(q->front == NULL) return 0;
    if(strcmp(q->front->task, task) == 0){
        Node * delNode = q->front;
        q->front = q->front->next;
        if(q->front == NULL) q->rear = NULL;

        free(delNode);
        return 1;
    }
    Node * curr = q->front;
    Node * prev = NULL;

    while(curr){
        if(strcmp(curr->task, task) == 0){
            Node * delNode = curr;
            prev->next = curr->next;
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next; 
    }
    return 0;
}

void printPendingTasks(Queue * q){
    Node * curr = q->front;
    while(curr){
        printf("%s", curr->task);
        if(curr->next!=NULL) printf(",");
        curr = curr->next;
    }
    printf("\n");
    return;
}

int main(){
    Queue * q = createQueue();
    int n;
    printf("Enter the number of commands : ");
    scanf("%d", &n);

    for(int i =0; i<n; i++){
        char input[50];
        scanf("%s", input);

        if(strcmp(input, "ADD") == 0){
            char taskName[101];
            fgets(taskName, 101, stdin);
            taskName[strcspn(taskName, "\n")] = '\0';
            enqueue(q, taskName);
            printf("Task added successfully\n");
        }
        else if(strcmp(input, "COMPLETE") == 0){
            char taskName[101];
            fgets(taskName, 101, stdin);
            taskName[strcspn(taskName, "\n")] = '\0';
            dequeue(q, taskName);
            printf("Task completed successfully\n");
        }
        else{
            char taskName[101];
            fgets(taskName, 101, stdin);
            taskName[strcspn(taskName, "\n")] = '\0';
            printf("Pending tasks are : ");
            printPendingTasks(q);
           
        }
    }
}