#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int coeff;
    int exp;
    struct Node *next;
} Node;
Node *createNode(int coeff, int exp)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->coeff = coeff;
    ;
    newNode->exp = exp;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node **head, int coeff, int exp)
{
    Node *newNode = createNode(coeff, exp);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
    return;
}

Node *addThePolynomials(Node *p1, Node *p2)
{
    if (p1 == NULL && p2 == NULL)
        return NULL;
    Node *res = NULL;
    while (p1 != NULL || p2 != NULL)
    {
        int coeff = 0;
        int exp = 0;
        if (p1 != NULL && (p2 == NULL || p1->exp > p2->exp))
        {
            coeff = p1->coeff;
            exp = p1->exp;
            p1 = p1->next;
        }
        else if (p2 != NULL && (p1 == NULL || p2->exp > p1->exp))
        {
            coeff = p2->coeff;
            exp = p2->exp;
            p2 = p2->next;
        }
        else
        {
            coeff = p1->coeff + p2->coeff;
            exp = p2->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        if (coeff != 0)
        {
            insertNode(&res, coeff, exp);
        }
    }
    return res;
}
Node *multiplyHelper(Node *x, Node *polynomial)
{
    Node *res = NULL;
    int coeff = x->coeff;
    int exp = x->exp;

    while (polynomial != NULL)
    {
        int newCoeff = polynomial->coeff * coeff;
        int newExp = polynomial->exp + exp;

        insertNode(&res, newCoeff, newExp);
        polynomial = polynomial->next;
    }

    return res;
}

Node *multiplyTwoPolynomials(Node *p1, Node *p2)
{
    if (p1 == NULL || p2 == NULL)
        return NULL;
    Node *prev = NULL;
    Node *curr = p1;

    while (curr != NULL)
    {
        Node *newLL = multiplyHelper(curr, p2);
        if (prev != NULL)
        {
            Node *temp = prev;
            prev = addThePolynomials(prev, newLL);
            free(temp);
        }
        else
            prev = newLL;
        curr = curr->next;
    }
    return prev;
}

void bubbleSort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;
    while (1)
    {
        int swapped = 0;
        Node *curr = head;
        while (curr->next != NULL)
        {
            if (curr->exp < curr->next->exp)
            {
                int temp = curr->exp;
                curr->exp = curr->next->exp;
                curr->next->exp = temp;
                swapped = 1;

                int tempCoeff = curr->coeff;
                curr->coeff = curr->next->coeff;
                curr->next->coeff = tempCoeff;
            }
            curr = curr->next;
        }
        if (swapped == 0)
            break;
    }
    return;
}

void printPolynomial(Node *head)
{
    while (head != NULL)
    {
        if (head->coeff != 0)
        {
            printf("%dx^%d ", head->coeff, head->exp);
            if (head->next != NULL)
            {
                printf("+ ");
            }
        }
        

        head = head->next;
    }
    printf("\n");
}

int main()
{
    Node *p1 = NULL;
    Node *p2 = NULL;

    int n1;
    int n2;

    printf("enter the n1: ");
    scanf("%d", &n1);

    for (int i = 0; i < n1; i++)
    {
        int coeff, exp;
        scanf("%d %d", &coeff, &exp);
        insertNode(&p1, coeff, exp);
    }

    printf("enter the n2 : ");
    scanf("%d", &n2);

    for (int i = 0; i < n2; i++)
    {
        int coeff, exp;
        scanf("%d %d", &coeff, &exp);
        insertNode(&p2, coeff, exp);
    }

    bubbleSort(p1);
    bubbleSort(p2);

    Node *res = multiplyTwoPolynomials(p1, p2);
    printf("Resultant polynomial: ");
    printPolynomial(res);
}