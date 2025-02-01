#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return;
}

Node *addToNumbers(Node *head1, Node *head2)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    Node *res = NULL;
    int carry = 0;
    while (head1 != NULL || head2 != NULL)
    {
        int coeff1 = (head1 != NULL) ? head1->data : 0;
        int coeff2 = (head2 != NULL) ? head2->data : 0;

        int sum = coeff1 + coeff2 + carry;
        insertNode(&res, sum % 10);
        carry = sum / 10;

        if (head1)
            head1 = head1->next;
        if (head2)
            head2 = head2->next;
    }

    if (carry > 0)
    {
        insertNode(&res, carry);
    }
    return res;
}

Node *reverse(Node *head, Node *prev)
{
    if (head == NULL)
        return prev;

    Node *temp = head->next;
    head->next = prev;

    return reverse(temp, head);
}

Node *printList(Node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    Node *head1 = NULL;
    Node *head2 = NULL;
    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        int curr;
        scanf("%d", &curr);
        insertNode(&head1, curr);
    }

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int curr;
        scanf("%d", &curr);
        insertNode(&head2, curr);
    }

    Node *res = addToNumbers(head1, head2);
    Node *result = reverse(res, NULL);

    printf("the result list is : ");
    printList(result);
}