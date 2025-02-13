#include <stdio.h>
#include <stdlib.h>
#define max_size 100001

typedef struct Node {
    char c;
    struct Node * next;
} Node;

Node * createNode(char c){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->c = c;

    return newNode;
}

typedef struct Queue{
    Node * front;
    Node * rear;
    int size;
} Queue;

Queue * createQueue(){
    Queue * q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}

void enqueue(Queue* q, char c){
    Node * newNode = createNode(c);
    if(q->front == NULL){
        q->front = newNode;
        q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
    q->size ++;

    return;
}

Node * dequeue(Queue * q){
    if(q->front == NULL) return NULL;
    Node * delNode = q->front;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    q->size --;

    return delNode;
}

int isEmpty(Queue * q){
    if(q->front == NULL) return 1;
    return 0;
}

Node * peek(Queue * q){
    if(q->front == NULL) return NULL;
    return q->front;
}

int main(){

    char input[max_size];
    scanf("%s", input);

    char output[max_size];
    int map[26] = {0};


    Queue * q = createQueue();

    int k =0;
    for(int i =0; input[i]!='\0'; i++){
        map[input[i] - 'a'] ++;
        if(map[input[i] - 'a'] >1){
           Node * delNode = dequeue(q);
           free(delNode);
        }
        else{
            enqueue(q, input[i]);
        }

        Node * peekNode = peek(q);
        if(peekNode == NULL){
            output[k++] = '-';
            output[k++] = '1';
        } 
        else output[k++] = peekNode->c;

    }
    output[k++] = '\0';

    printf("%s\n", output);
}