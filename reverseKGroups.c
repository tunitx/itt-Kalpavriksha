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

struct ListNode* reverse(struct ListNode* head, int k) {
    struct ListNode* prev = NULL;
    while (head != NULL && k != 0) {
        struct ListNode* temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
        k--;
    }
    return prev;
}

struct ListNode* helper(struct ListNode* head, int k) {
    if (head == NULL) return head;
    struct ListNode* curr = head;
    int n = k;
    while (curr != NULL && n != 1) {
        curr = curr->next;
        n--;
    }

    if (curr == NULL) return head;

    struct ListNode* temp = curr->next;
    struct ListNode* new_head = reverse(head, k);

    head->next = helper(temp, k);
    return new_head;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    return helper(head, k);
}

int main() {
    char input[] = "1,2,3,4,5";
    int k = 2;

    ListNode* head = createLinkedList(input);

    printf("Original list: ");
    printLinkedList(head);

    head = reverseKGroup(head, k);

    printf("Reversed list in groups of %d: ", k);
    printLinkedList(head);

    return 0;
}