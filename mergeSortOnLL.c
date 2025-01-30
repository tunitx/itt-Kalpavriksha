// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 200

typedef struct Node {
    int data;
    struct Node * next;
} Node;

void add_node(Node ** head, int data){
    Node * node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    
    if(*head == NULL){
        *head = node;
    }
    else{
        Node * temp = *head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = node;
    }
    return;
}
void split_list(Node * head, Node ** front, Node ** back){
    Node * slow = head;
    Node * fast = head->next;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

Node * merge(Node * left, Node * right){
    if(!left) return right;
    if(!right) return left;
    
    Node * res = NULL;
    if(left->data <= right->data){
        res = left;
        res->next = merge(left->next, right);
    } else{
        res = right;
        res->next = merge(left, right->next);
    }
    
    return res;
}

void print_list(Node * head){
    printf("Curr Linked list: ");
    while(head!=NULL){
        if(head->next == NULL)
            printf("%d", head->data);
        else
            printf("%d,", head->data);
        head = head->next;
    }
    printf("\n");
    return;
}
void merge_sort(Node ** headref){
    Node * head = *headref;
    if(head == NULL || head->next == NULL){
        return;
    }
    
    Node * front = NULL;
    Node * back = NULL;
    split_list(head, &front, &back);
    
    merge_sort(&front);
    merge_sort(&back);
    
    *headref =  merge(front, back);
}

int main() {
    // Write C code here
    char str[max_size];
    fgets(str, max_size, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    char * delim = ",";
    char * token = strtok(str, delim);
    Node * head = NULL;
    
    while(token!=NULL){
        add_node(&head, atoi(token));
        token = strtok(NULL, delim);
    }
    
    print_list(head);
    merge_sort(&head);
    print_list(head);
    
    return 0;
}