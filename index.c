#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* createNode(int data){
    Node* newNode=(Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

void addAtEnd(Node** head,int key){
    Node* newNode=createNode(key);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    Node*curr=*head;
    while(curr->next!=NULL){
        curr=curr->next;
    }
    curr->next=newNode;
}

void addAtbeginning(Node** head,int data){
    Node* newNode=createNode(data);
    newNode->next=*head;
    *head=newNode;
}
void addAtGivenPosition(Node** head,int pos,int data){
    if(pos<=0){
        printf("Invalid Position\n");
        return;
    }
    Node *newNode=createNode(data);
    if(pos==1){
        newNode->next=*head;
        *head=newNode;
        return;
    }
    Node* curr=*head;
    int i=1;
    while(curr!=NULL && i<pos-1){
        curr=curr->next;
        i++;
    }
    if(curr==NULL){
        printf("Invalid Position");
        free(newNode);
        return;
    }
    newNode->next=curr->next;
    curr->next=newNode;
}

void updateAtGivenPosition(Node** head,int pos,int data){
    if(pos<=0){
        printf("Invalid Position\n");
        return;
    }
    Node* curr=*head;
    int i=0;
    while(curr!=NULL && i<pos-1){
        curr=curr->next;
        i++;
    }
    if(curr==NULL){
        printf("Invalid Position");
        return;
    }
    curr->data=data;
}

void deleteFirst(Node** head){
    if(*head==NULL){
        return;
    }
    Node* temp=*head;
    *head=(*head)->next;
    free(temp);
}

void deleteLast(Node** head){
    if(*head==NULL) {
        return;
    }
    if((*head)->next==NULL){
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp=*head;
    Node* prev=NULL;
    while(temp->next != NULL) {
        prev=temp;
        temp=temp->next;
    }
    prev->next=NULL;
    free(temp);
}

void deleteAtGivenPosition(Node** head,int pos){
    if(*head==NULL){
        return;
    }
    if(pos<1){
        return;
    }
    if(pos==1){
        Node* temp=*head;
        *head=(*head)->next;
        free(temp);
        return;
    }

    Node* temp=*head;
    Node* prev=NULL;
    int i=1;

    while(temp!=NULL && i<pos){
        prev=temp;
        temp=temp->next;
        i++;
    }
    if(temp==NULL){
        return;
    }
    prev->next=temp->next;
    free(temp);
}

void printList(Node **head){
    Node *curr = *head;
    while(curr!=NULL){
        printf("%d ",curr->data);
        curr=curr->next;
    }
    printf("\n");
}

int main(){
    Node* head=NULL;
    int noOfOperations;
    scanf("%d",&noOfOperations);

    while(noOfOperations>0){
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                int key;
                scanf("%d",&key);
                addAtEnd(&head,key);
                printList(&head);
                break;
            }
            case 2:{
                int key;
                scanf("%d",&key);
                addAtbeginning(&head,key);
                printList(&head);
                break;
            }
            case 3:{
                int key;
                int pos;
                scanf("%d",&pos);
                scanf("%d",&key);
                addAtGivenPosition(&head,pos,key);
                printList(&head);
                break;
            }
            case 4:{
                printList(&head);
                break;
            }
            case 5:{
                int key;
                int pos;
                scanf("%d",&pos);
                scanf("%d",&key);
                updateAtGivenPosition(&head,pos,key);
                printList(&head);
                break;
            }
            case 6:{
                deleteFirst(&head);
                printList(&head);
                break;
            }
            case 7:{
                deleteLast(&head);
                printList(&head);
                break;
            }
            case 8:{
                int pos;
                scanf("%d",&pos);
                deleteAtGivenPosition(&head,pos);
                printList(&head);
                break;
            }
            default:{
                printf("Please choose between 1 to 8\n");
                break;
            }
        }
        noOfOperations--;
    }

    return 0;
}