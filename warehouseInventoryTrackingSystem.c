#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000

typedef struct Node {
    char * item;
    int count;

    struct Node * next;
} Node;

Node * createNode(char * item, int count){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->item = strdup(item);
    newNode->count = count;

    return newNode;
}

typedef struct HashMap{
    Node * table [MAXSIZE];
} HashMap;

HashMap * createHashMap(){
    HashMap * hm = (HashMap *)malloc(sizeof(HashMap));
    for(int i =0; i<MAXSIZE; i++){
        hm->table[i] = NULL;
    }
    return hm;
}

unsigned int hashFunction(char * item){
    unsigned int key = 0;
    while(*item){
        key = (key + *item)%MAXSIZE;
        item ++; 
    }
    return key;
}

void put(HashMap * hm, char * item, int count){
    int key = hashFunction(item);
    Node * keyNode = hm->table[key];
        while(keyNode){
            if(strcmp(keyNode->item, item) == 0){
                keyNode->count += count;
                return;
            }
            keyNode = keyNode->next;
        }
    
    Node * newNode = createNode(item, count);
    newNode->next = hm->table[key];
    hm->table[key] = newNode;
    return;
}

void update(HashMap * hm, char * item, int count){
    int key = hashFunction(item);
    Node * keyNode = hm->table[key];
    while(keyNode){
        if(strcmp(keyNode->item, item) == 0){
            keyNode->count = count;
            return;
        }
        keyNode = keyNode->next;
    }
    return;
}


Node * get(HashMap * hm, char * item){
    int key = hashFunction(item);
    Node * keyNode = hm->table[key];
    while(keyNode){
        if(strcmp(keyNode->item, item) == 0){
            return keyNode;
        }
        keyNode = keyNode->next;
    }
    return NULL;
}

int main (){

    HashMap * hm = createHashMap();
    int n;
    printf("Enter the number of commands : ");
    scanf("%d", &n);

    for(int i =0; i<n; i++){
        char input[MAXSIZE];
        scanf("%s", input);
        if(strcmp(input, "ADD") == 0){
            char itemName[MAXSIZE];
            scanf("%s", itemName);
            int count;
            scanf("%d", &count);

            put(hm, itemName, count);

            printf("Item added\n");
        }
        else if(strcmp(input, "UPDATE") == 0){
            char itemName[MAXSIZE];
            scanf("%s", itemName);
            int count;
            scanf("%d", &count);
            
            update(hm, itemName, count);

            printf("item updated\n");
        }
        else{
            char itemName[MAXSIZE];
            scanf("%s", itemName);
            Node * getNode =  get(hm, itemName);
            if(getNode == NULL) printf("Item not found\n");
            else printf("%s : %d\n", getNode->item, getNode->count);
        }
    }
}