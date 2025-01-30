#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

ListNode* createLinkedList(char* str) {
    ListNode *head = NULL, *tail = NULL;
    char *token = strtok(str, ",");

    while (token != NULL) {
        int val = atoi(token);
        ListNode* newNode = createNode(val);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        token = strtok(NULL, ",");
    }

    return head;
}

void printLinkedList(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *dummy = (ListNode *)malloc(sizeof(ListNode));
    ListNode *curr = dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL) {
        int d1 = (l1 != NULL) ? l1->val : 0;
        int d2 = (l2 != NULL) ? l2->val : 0;

        int sum = d1 + d2 + carry;
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        new_node->val = sum % 10;
        new_node->next = NULL; 
        curr->next = new_node;
        curr = new_node;

        carry = sum / 10;

        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }

    if (carry > 0) {
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        new_node->val = carry;
        new_node->next = NULL;
        curr->next = new_node;
    }

    return dummy->next;
}

int main() {
    char input1[] = "2,4,3";
    char input2[] = "5,6,4";

    ListNode* l1 = createLinkedList(input1);
    ListNode* l2 = createLinkedList(input2);

    printf("List 1: ");
    printLinkedList(l1);

    printf("List 2: ");
    printLinkedList(l2);

    ListNode* result = addTwoNumbers(l1, l2);

    printf("Result: ");
    printLinkedList(result);

    return 0;
}