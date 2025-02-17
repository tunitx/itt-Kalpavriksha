#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node
{
    char *room;
    struct Node *next;
} Node;

Node *createNode(char *room)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->room = strdup(room);

    return newNode;
}

typedef struct HashMap
{
    Node *table[MAX];
} HashMap;

HashMap *createHashMap()
{
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < MAX; i++)
    {
        hm->table[i] = NULL;
    }

    return hm;
}

unsigned int hashFunction(char *str)
{
    unsigned int key = 0;
    while (*str)
    {
        key = (key + *str) % MAX;
        str++;
    }
    return key;
}

void put(HashMap *hm, char *room)
{
    int key = hashFunction(room);
    Node *newNode = createNode(room);
    newNode->next = hm->table[key];
    hm->table[key] = newNode;
}

void delete(HashMap *hm, char *room)
{
    int key = hashFunction(room);
    Node *keyNode = hm->table[key];
    Node *prev = NULL;

    while (keyNode)
    {
        if (strcmp(keyNode->room, room) == 0)
        {
            if (prev == NULL)
            {
                hm->table[key] = keyNode->next;
            }
            else
            {
                prev->next = keyNode->next;
            }
            free(keyNode);
            free(keyNode->room);
            return;
        }
        prev = keyNode;
        keyNode = keyNode->next;
    }
}

int get(HashMap *hm, char *room)
{
    int key = hashFunction(room);
    Node *keyNode = hm->table[key];
    while (keyNode)
    {
        if (strcmp(keyNode->room, room) == 0)
        {
            return 1;
        }
        keyNode = keyNode->next;
    }
    return 0;
}

int main()
{
    HashMap *hm = createHashMap();
    int n;
    printf("Enter the number of commands : ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        char input[1000];
        fgets(input, 1000, stdin);
        input[strcspn(input, "\n")] = '\0';

        char *currToken = strtok(input, " ");
        if (strcmp(currToken, "TURN_ON") == 0)
        {
            char *room = strtok(NULL, " ");
            if(!get(hm, room)){
                put(hm, room);
                printf("The room %s light has been turned on.\n", room);
            }
            else{
                printf("The room %s light is already on.\n", room);
            }
            
        }
        else if (strcmp(currToken, "TURN_OFF") == 0)
        {
            char *room = strtok(NULL, " ");
            if(get(hm, room)){
                delete(hm, room);
                printf("The room %s light has been turned off.\n", room);
            }
            else{
                printf("The room %s light is already off.\n", room);
            }
           
        }
        else
        {
            char *room = strtok(NULL, " ");
            int status = get(hm, room);
            if (status)
                printf("The room Light is On.\n");
            else
                printf("The room light is off.\n");
        }
    }
}