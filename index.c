// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node * next;
}Node;

Node * create_node(int value){
    Node * new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    
    return new_node;
}

int main() {
    int N, K;
    printf("enter the no of ops & size of window: ");
    scanf("%d %d", &N, &K);
    
    Node * head = NULL;
    Node * tail = NULL;
    int size = 0;
    int sum =0;
    
    for(int i =0; i<N; i++){
        char op;
        printf("enter the operation : ");
        scanf(" %c", &op);
        
        if(op == 'A'){
            int X;
            scanf("%d", &X);
            Node * new_node = create_node(X);
            if(tail == NULL){
                head = tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = new_node;
            }
            
            sum += X;
            size ++;
            
            if(size > K){
                Node * temp = head;
                head = head->next;
                sum -= temp->value;
                free(temp);
                size --;
            }
        }
        else if(op == 'S'){
            printf("the sum is %d\n", sum);
        }
    }
    while(head!=NULL){
        Node * temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}