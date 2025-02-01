#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_size 10000

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createNode(int data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node ** head, int data){
    Node * newNode = createNode(data);
    if(*head == NULL)
        *head = newNode;
    else{
        Node * temp = *head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return;
}

Node * helper(Node * head, int k){
    Node * res = NULL;
    while(head->next!= head){
        int i =1;
        while(i<k-1){
            i++;
            head = head->next;
        }
        Node * delNode = head->next;
        head->next = head->next->next;
        insertNode(&res, delNode->data);
        free(delNode);
        head = head->next;
    }
    insertNode(&res, head->data);
    return res;
}

int parseToken(char * token){
    if(strlen(token) <= 4 || strncmp("ITT/", token, 4)!=0) return -1;
    int n =0;

    for(int i =4; token[i]!='\0'; i++){
        if(!isdigit(token[i])) return -1;
        n = n*10 + (token[i] - '0');
    }
    if(n>999) return -1;
    return n;
}

Node * parseInput(int * k){
    char input[max_size];
    printf("enter the linked list (in space separated): ");
    fgets(input, max_size, stdin);
    input[strcspn(input, "\n")] = '\0';
    Node * head = NULL;

    char * token = strtok(input, " ");
    while(token!=NULL){
        int res = parseToken(token);
        if(res == -1) return NULL;
        insertNode(&head, res);
        token = strtok(NULL, " ");
    }

    Node * temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = head;

    printf("enter k: ");
    scanf("%d", &(*k));

    return head;
}

void printList(Node * head){
    while(head!=NULL){
        printf("ITT/%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(){
    int k =0;
    Node * head = parseInput(&k);
    if(head == NULL) printf("empty");
    Node * res = helper(head, k);
    printList(res);
    return 0;
}