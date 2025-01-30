#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode* oddEvenList(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    ListNode *odd = head;
    ListNode *even = head->next;
    ListNode *evenHead = even;

    while (even != NULL && even->next != NULL) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}

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

ListNode* reverse(ListNode* head, ListNode* prev) {
    if (head == NULL) return prev;
    ListNode* temp = head->next;
    head->next = prev;
    return reverse(temp, head);
}

bool isPalindrome(ListNode* head) {
    if (head == NULL) return true;

    ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *new_head = reverse(slow, NULL);

    while (new_head != NULL) {
        if (new_head->val != head->val) return false;
        new_head = new_head->next;
        head = head->next;
    }

    return true;
}

int main() {
    char input[] = "2,1,3,5,6,4,7";
    ListNode* head = createLinkedList(input);

    printf("Original list: ");
    printLinkedList(head);

    head = oddEvenList(head);

    printf("Reordered list: ");
    printLinkedList(head);

    if (isPalindrome(head)) {
        printf("The list is a palindrome.\n");
    } else {
        printf("The list is not a palindrome.\n");
    }

    return 0;
}