#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int page;
    struct Node *next;
} Node;

Node *createNode(int page)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->page = page;

    return newNode;
}

typedef struct Stack
{
    Node *top;
    int size;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void push(Stack *stack, int page)
{
    Node *newNode = createNode(page);
    if (stack->top == NULL)
    {
        stack->top = newNode;
    }
    else
    {
        newNode->next = stack->top;
        stack->top = newNode;
    }
    stack->size++;
}

int pop(Stack *stack)
{
    if (stack->top == NULL)
        return -1;
    Node *delNode = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    int data = delNode->page;
    free(delNode);

    return data;
}

int isEmpty(Stack *stack)
{
    return stack->size == 0;
}

void reverse(int *arr, int n)
{
    int i = 0, j = n - 1;

    while (i < j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void bubbleSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int *arr, int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(",");
    }
}

void printStack(Stack *stack)
{
    int arr[stack->size];
    int n = stack->size;
    for (int i = 0; i < n; i++)
    {
        arr[i] = pop(stack);
    }

    reverse(arr, n);
    for (int i = 0; i < n; i++)
    {
        push(stack, arr[i]);
    }

    bubbleSort(arr, n);
    printArray(arr, n);
}

int main()
{
    Stack *stack = createStack();
    int n;
    printf("enter the number of commands: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char input[1000];
        scanf("%s", input);
        if (strcmp(input, "BOOKMARK") == 0)
        {
            int page;
            scanf("%d", &page);
            push(stack, page);
            printf("Bookmark added\n");
        }
        else if (strcmp(input, "DELETE") == 0)
        {
            int popped = pop(stack);
            if (popped == -1)
                printf("No bookmarked pages yet\n");
            else
                printf("the deleted bookmark is %d\n", popped);
        }
        else
        {
            if (stack->size == 0)
            {
                printf("No bookmarks available\n");
            }
            else
            {
                printf("The bookmarked pages are : ");
                printStack(stack);
            }
        }
    }
}
