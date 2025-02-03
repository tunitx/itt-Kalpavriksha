#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * sortAroundPivot(Node * head, int pivot){
    Node * lessHead = NULL, *lessTail = NULL;
    Node *equalHead = NULL, * equalTail = NULL;
    Node * moreHead = NULL, *moreTail = NULL;

    while(head!=NULL){
        if(head->data < pivot){
            if(lessHead == NULL){
                lessHead = head = lessTail;
            }
            else{
                lessTail->next = head;
                lessTail = head;
            }
        }
        else if(head->data == pivot){
            if(equalHead == NULL){
                equalHead = head = equalTail;
            }
            else{
                equalTail->next = head;
                equalTail = head;
            }
        }
        else{
            if(moreHead == NULL){
                moreHead = head = moreTail;
            }
            else{
                moreTail->next = head;
                moreTail = head;
            }
        }
        head = head->next;
    }
    if(lessTail != NULL)
        lessTail->next = equalHead;
    if(equalTail!=NULL)
        equalTail->next = moreHead;
    if(moreTail!=NULL)
        moreTail->next = NULL;

    return (lessHead) ? lessHead : (equalHead ? equalHead : moreHead);
}

int main(){

}