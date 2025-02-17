#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *movie;
    int rating;

    struct Node *next;
} Node;

Node *createNode(char *movie, int rating)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->movie = strdup(movie);
    newNode->rating = rating;

    return newNode;
}

typedef struct PriorityQueue
{
    Node *front;
} PriorityQueue;

PriorityQueue *createPriorityQueue()
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->front = NULL;

    return pq;
}

Node *isPresent(PriorityQueue *pq, char *movie)
{
    Node *curr = pq->front;
    while (curr)
    {
        if (strcmp(curr->movie, movie) == 0)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void add(PriorityQueue *pq, char *movie, int rating)
{
    Node *front = pq->front;
    Node *newNode = createNode(movie, rating);
    if (front == NULL)
    {
        pq->front = newNode;
        return;
    }

    if (front->rating < rating)
    {
        newNode->next = pq->front;
        pq->front = newNode;
        return;
    }
    while (front->next && front->next->rating >= rating)
        front = front->next;

    newNode->next = front->next;
    front->next = newNode;

    return;
}

void delete(PriorityQueue *pq, char *movie)
{
    Node *front = pq->front;
    Node *prev = NULL;

    while (front)
    {
        if (strcmp(front->movie, movie) == 0)
        {
            if (prev == NULL)
            {
                pq->front = front->next;
            }
            else
            {
                prev->next = front->next;
            }
            free(front->movie);
            free(front);
            return;
        }
        prev = front;
        front = front->next;
    }
}

Node *top(PriorityQueue *pq)
{
    return pq->front;
}

int main()
{
    int n;
    printf("enter the number of commands : ");
    scanf("%d", &n);
    getchar();
    PriorityQueue *pq = createPriorityQueue();

    for (int i = 0; i < n; i++)
    {
        char input[100];
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = '\0';

        char *token = strtok(input, " ");
        if (strcmp(token, "RATE") == 0)
        {
            char *movie = strtok(NULL, " ");
            int rating = atoi(strtok(NULL, " "));

            Node *present = isPresent(pq, movie);
            if (present == NULL)
                add(pq, movie, rating);
            else
            {
                delete (pq, movie);
                add(pq, movie, rating);
            }

            printf("Movie rating added successfully.\n");
        }
        else if (strcmp(token, "REMOVE") == 0)
        {
            char *movie = strtok(NULL, " ");
            delete (pq, movie);
            printf("Movie Rating removed successfully.\n");
        }
        else
        {
            Node *movie = top(pq);
            if (movie)
                printf("The highest rated movie is : %s : %d\n", movie->movie, movie->rating);
            else
                printf("No movie available.\n");
        }
    }
}