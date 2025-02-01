#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data  = data;
    newNode->next = NULL;

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

Node * addTwoNumbers(Node * head1, Node * head2){
    if(head1 == NULL) return head2;
    if(head2 == NULL) return head1;

    int carry = 0;
    Node * res = NULL;
    while(head1!=NULL || head2!=NULL){
        int h1Data = (head1 != NULL) ? head1->data : 0;
        int h2Data = (head2!= NULL) ? head2->data : 0;

        int sum = h1Data + h2Data + carry;
        insertNode(&res, sum%10);
        carry = sum/10;
        if(head1!=NULL) head1 = head1->next;
        if(head2!=NULL) head2 = head2->next;
    }

    if(carry > 0){
        insertNode(&res, carry);
    }
    return res;
}

Node * multiplyHelper(int x, Node * head){
    int carry = 0;
    Node * res = NULL;
    while(head!= NULL){
        int m = head->data * x + carry;
        insertNode(&res, m%10);
        carry = m/10;
        head = head->next;
    }
    if(carry > 0){
        insertNode(&res, carry);
    }
    return res;
}

void printList(Node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

Node * multiplyTwoNumbers(Node * head1, Node * head2){
    Node * prev = NULL;
    Node * zeroPadding = NULL;
    while(head1 != NULL){
        int multiplier = head1->data;
        Node * newLL = multiplyHelper(multiplier, head2);
        // printList(newLL);
        if(zeroPadding!=NULL){
            Node * temp = zeroPadding;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = newLL;
            newLL = zeroPadding;
        }
        if(prev!=NULL){
            prev = addTwoNumbers(prev, newLL);
        }
        else{
            prev = newLL;
        }
        head1 = head1->next;
        insertNode(&zeroPadding, 0);
    }
    return prev;
}


Node *reverse(Node *head, Node *prev)
{
    if (head == NULL)
        return prev;

    Node *temp = head->next;
    head->next = prev;

    return reverse(temp, head);
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
    if(n>m){
        Node * temp = head1;
        head1 = head2;
        head2 = temp;
    }

    Node *res = multiplyTwoNumbers(head1, head2);
    Node *result = reverse(res, NULL);

    printf("the result list is : ");
    printList(result);

    return 0;

}