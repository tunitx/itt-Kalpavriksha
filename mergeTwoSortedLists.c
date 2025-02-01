#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;

    return newNode;
}

void insertNode(Node ** head, int data){
    Node * newNode = createNode(data);
    if(*head == NULL){
        *head = newNode;
    }
    else{
        Node * temp = *head;
        while(temp->next!=NULL) temp = temp->next;
        temp->next = newNode;
    }
    return;
}

Node * mergeSortedLists(Node * head1, Node * head2){
    Node * dummy = createNode(0);
    Node * temp = dummy;

    while(head1!=NULL && head2!=NULL){
        if(head1->data <= head2->data){
            temp->next = head1;
            temp = head1;
            head1 = head1->next;
        }
        else{
            temp->next = head2;
            temp = head2;
            head2 = head2->next;
        }
    }

    if(head1!=NULL){
        temp->next = head1;
    }
    if(head2!=NULL){
        temp->next = head2;
    }

    return dummy->next;
}

void printList(Node * head){
    while(head!=NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(){
    Node *head1 = NULL;
    Node *head2 = NULL;
    int n, m;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        int curr;
        scanf("%d", &curr);
        insertNode(&head1, curr);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int curr;
        scanf("%d", &curr);
        insertNode(&head2, curr);
    }

    Node * res = mergeSortedLists(head1, head2);

    printf("l1 : ");
    printList(head1);
    printf("l2 : ");
    printList(head2);

    printf("merged list : ");
    printList(res);
}