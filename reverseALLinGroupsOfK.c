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

void insertNode(Node ** head, int data){
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

Node * reverse(Node * head, int k){
    Node * prev = NULL;
    while(head && k!=0){
        Node * temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
        k--;
    }
    return prev;
}

Node * reverseKNodes(Node * head, int k){
    if(head == NULL || k == 0) return head;

    Node * curr = head;
    int n = k;
    while(curr && n!=1){
        curr = curr->next;
        n--;
    }
    if(curr == NULL) return head;

    Node * nextHead = curr->next;
    Node * newHead = reverse(head, k);
    head->next = reverseKNodes(nextHead, k);
    return newHead;
}

int main(){

}