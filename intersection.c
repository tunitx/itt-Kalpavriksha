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

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode* curr1 = headA;
    ListNode* curr2 = headB;

    while (curr1 != NULL && curr2 != NULL) {
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    if (curr1 == NULL) {
        while (curr2 != NULL) {
            headB = headB->next;
            curr2 = curr2->next;
        }
    } else {
        while (curr1 != NULL) {
            curr1 = curr1->next;
            headA = headA->next;
        }
    }

    while (headA != NULL && headB != NULL && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }

    if (headA == NULL || headB == NULL) return NULL;

    return headA;
}

int main() {
    char inputA[] = "4,1,8,4,5";
    char inputB[] = "5,6,1,8,4,5";
    int skipA = 2;
    int skipB = 3;

    ListNode* headA = createLinkedList(inputA);
    ListNode* headB = createLinkedList(inputB);

    ListNode* tempA = headA;
    for (int i = 0; i < skipA; i++) {
        tempA = tempA->next;
    }

    ListNode* tempB = headB;
    for (int i = 0; i < skipB; i++) {
        tempB = tempB->next;
    }

    tempB->next = tempA;

    printf("List A: ");
    printLinkedList(headA);

    printf("List B: ");
    printLinkedList(headB);

    ListNode* intersection = getIntersectionNode(headA, headB);

    if (intersection != NULL) {
        printf("Intersected at '%d'\n", intersection->val);
    } else {
        printf("No intersection\n");
    }

    return 0;
}