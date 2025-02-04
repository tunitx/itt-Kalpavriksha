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

Node * reorder(Node * head){
    Node * slow = head, *fast = head;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    Node * p2 = reverse(slow->next);
    slow->next = NULL;
    Node * p1 = head;

    while(p2){
        Node * temp1 = p1->next;
        Node * temp2 = p2->next;

        p1->next = p2;
        p1 = temp1;

        p2->next = p1;
        p2 = temp2;
    }
    return head;
}

int main(){

}