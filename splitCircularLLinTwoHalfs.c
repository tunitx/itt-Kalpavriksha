#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insert(Node ** head, int data){
    Node * newNode = createNode(data);
    if(*head == NULL)
        *head = newNode;
    else{
        Node * temp = *head;
        while(temp->next!=NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    return;
}

void splitInTwoHalfs(Node * head, Node ** h1, Node ** h2){
    Node *temp = head;
    while(temp->next!=head)
        temp = temp->next;
    temp->next = NULL;

    Node * slow = head, *fast = head;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    *h2 = slow->next;
    *h1 = head;
    slow->next = head;

    temp = h2;
    while(temp->next!=NULL)
        temp = temp->next;
    temp->next = h2;

    return;

}

int main(){

}