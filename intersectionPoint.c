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
Node *getIntersectionNode(Node  *heada, Node *headb) {
    Node * c1 = heada;
    Node  * c2 = headb;

    while(c1!=NULL && c2!=NULL){
        if(c1 == c2) return c1;
        c1 = c1->next;
        c2 = c2->next;
    }

    if(c1 == NULL && c2 == NULL) return NULL;

    if(c1!=NULL){
        while(c1!=NULL){
            c1 = c1->next;
            heada = heada->next;
        }
    }
    else if(c2!=NULL){
        while(c2!=NULL){
            c2 = c2->next;
            headb = headb->next;
        }
    }

    while(heada!=NULL && headb!=NULL) {
        if(heada == headb) return heada;
        heada = heada->next;
        headb = headb->next;
    }
    return NULL;
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