#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 10000
#define table_size 10000


typedef struct Node {
    char file_name[max_size];
    struct Node * next;
} Node;

typedef struct HashTable{
    Node * table[table_size];
} HashTable;

Node * createNode(char * fileName){
    Node * newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->file_name, fileName);
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node ** head, char *  data){
    Node * newNode = createNode(data);
    if(*head == NULL)
        *head = newNode;
    else{
        Node * temp = *head;
        while(temp->next!=NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    return;
}


int hashFunction(char * str){
    int key =0;
    while(*str){
        key = (key*31 + *str++)%table_size;
    }
    return key;
}

int insert(HashTable * ht, char * fileName){
    int key = hashFunction(fileName);
    Node * curr = ht->table[key];
    while(curr!=NULL){
        if(strcmp(curr->file_name, fileName)==0){
            printf("duplicate found, aborting insertion\n");
            return 0;
        }
        curr = curr->next;
    }
    Node * newNode = createNode(fileName);
    newNode->next = ht->table[key];
    ht->table[key] = newNode;
    return 1;
}

int contains(HashTable * ht, char * fileName){
    int key = hashFunction(fileName);
    Node * curr = ht->table[key];
    while(curr!=NULL){
        if(strcmp(curr->file_name, fileName) == 0){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int delete(HashTable * ht, char * fileName){
    int key = hashFunction(fileName);
    Node * curr = ht->table[key];
    Node * prev = NULL;
    while(curr){
        if(strcmp(curr->file_name, fileName) == 0){
            if(prev!=NULL){
                prev->next = curr->next;
            }
            else{
                ht->table[key] = curr->next;
            }
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }

    return 0;
}


HashTable * createHashTable(){
    HashTable * ht = (HashTable *)malloc(sizeof(HashTable));
    for(int i =0; i<table_size; i++){
        ht->table[i] = NULL;
    }
    return ht;
}

Node *parseInput(){
    char input[max_size];
    fgets(input, max_size, stdin);
    HashTable * ht = createHashTable();
    input[strcspn(input, "\n")] = '\0';
    Node * head = NULL;

    char * token = strtok(input, " ");
    while(token!=NULL){
        if(!contains(ht, token)){
            insert(ht, token);
            insertNode(&head, token);
        }
        token = strtok(NULL, " ");
    }

    return head;
}

void printList(Node * head){
    while(head!=NULL){
        printf("%s ", head->file_name);
        head = head->next;
    }
    printf("\n");
}


int main(){

    Node * head = parseInput();

    printList(head);

    return 0;


}