#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 100000

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *kAltReverse(Node *head, int k) {
    Node *curr = head;
    Node *next = NULL;
    Node *prev = NULL;
    int count = 0;

    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (head != NULL) {
        head->next = curr;
    }

    count = 0;
    while (count < k - 1 && curr != NULL) {
        curr = curr->next;
        count++;
    }

    if (curr != NULL) {
        curr->next = kAltReverse(curr->next, k);
    }

    return prev;
}

void add_to_ll(Node **head, int data) {
    Node *curr_node = (Node *)malloc(sizeof(Node));
    curr_node->data = data;
    curr_node->next = NULL;

    if (*head == NULL) {
        *head = curr_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr_node;
    }
    return;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    char str[max_size];
    printf("enter the linked list in space separated string format: ");
    fgets(str, max_size, stdin);
    str[strcspn(str, "\n")] = '\0';

    int k;
    printf("enter K : ");
    scanf("%d", &k);

    char *delim = " ";
    char *token = strtok(str, delim);
    Node *head = NULL;

    while (token != NULL) {
        add_to_ll(&head, atoi(token));
        token = strtok(NULL, delim);
    }

    head = kAltReverse(head, k);

    print_list(head);

    return 0;
}