#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode =  (Node * )malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

int size(Node * top){
    if(top == NULL){
        printf("the len is : 0");
        return 0;
    } 
    int len =0;
    while(top!=NULL){
        len ++;
        top = top->next;
    }
    printf("the len is : %d\n", len);
    return len;
}

int isEmpty(Node * top){
    if(top == NULL){
        printf("the stack is Empty\n");
        return 1;
    } 
    printf("the stack isnt empty\n");
    return 0;
}

void push(Node ** top, int data){
    Node * newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

void peek(Node * top){
    if(top == NULL){
        printf("stack is Empty\n");
        return;
    }

    printf("Peek : %d\n", top->data);
}

int pop(Node ** top){
    if(*top == NULL){
        printf("stack underflow");
        return -1;
    }
    int data  = (*top)->data;
    *top = (*top)->next;
    printf("the element popped is : %d\n", data);
    return data;
}



int main(){
    Node * head = NULL;
    isEmpty(head);
    push(&head, 10);
    push(&head, 11);
    peek(head);
    size(head);
    push(&head, 13);
    pop(&head);

}