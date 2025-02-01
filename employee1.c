#include <stdio.h>
#include <stdlib.h>
#define max_size 10000
#include <string.h>
#include <ctype.h>

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

void bubbleSort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;
    while (1)
    {
        Node *curr = head;
        int swapped = 0;
        while (curr->next != NULL)
        {
            if (curr->data > curr->next->data)
            {
                int temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = 1;
            }
            curr = curr->next;
        }
        if (swapped == 0)
            break;
    }
    return;
}

void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);
    if (*head == NULL)
        *head = newNode;
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
}

Node *findUnique(Node *head)
{
    Node *res = NULL;
    while (head != NULL && head->next != NULL)
    {
        while (head->next != NULL && head->data == head->next->data)
            head = head->next;

        insertNode(&res, head->data);
        if (head != NULL)
            head = head->next;
    }
    if(head!=NULL) insertNode(&res, head->data);
    return res;
}

Node *findIntersection(Node *head)
{
    Node *res = NULL;
    while (head != NULL && head->next != NULL)
    {
        if (head->data == head->next->data)
        {
            insertNode(&res, head->data);
            while (head->next != NULL && head->data == head->next->data)
                head = head->next;
        }
        if (head != NULL)
            head = head->next;
    }
    return res;
}

void printList(Node *head)
{
    while (head != NULL)
    {
        printf("ITT/%d, ", head->data);
        head = head->next;
    }
    printf("\n");
}

int parseToken(char *token) {
    if (strlen(token) <= 4 || strncmp(token, "ITT/", 4) != 0)
        return -1;

    int n = 0;
    for (int i = 4; token[i] != '\0'; i++) {
        if (!isdigit(token[i]))  
            return -1;
        n = n * 10 + (token[i] - '0');  
    }
    return n;
}
Node* readInput() {
    char input[max_size];
    Node *head = NULL;

    fgets(input, max_size, stdin);
    input[strcspn(input, "\n")] = '\0';
    
    char *token = strtok(input, " ");
    while (token != NULL) {
        int res = parseToken(token);
        if (res == -1) {
            printf("Invalid input: %s\n", token);
            return NULL;
        }
        insertNode(&head, res);
        token = strtok(NULL, " ");
    }
    return head;
}

int main() {
    Node *head1 = NULL, *head2 = NULL;

    printf("Enter the players who play football (in space-separated string): ");
    head1 = readInput();
    if (head1 == NULL) return 0;

    printf("Enter the players who play tennis (in space-separated string): ");
    head2 = readInput();
    if (head2 == NULL) return 0;
   

    Node * temp = head1;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = head2;
    bubbleSort(head1);
    Node *intersection = findIntersection(head1);
    Node *unique = findUnique(head1);

    printf("the employees which play both the games are: ");
    printList(intersection);

    printf("all unique ids from both the games are : ");
    printList(unique);
}