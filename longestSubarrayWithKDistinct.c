#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 128
#define max_size 1000001

typedef struct Node {
    char c;
    int count;
    struct Node * next;
} Node;


Node * createNode(char c, int count){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->c = c;
    newNode->count = count;

    return newNode;
}

typedef struct HashMap{
    Node * bucket[MAP_SIZE];
    int size;
} HashMap;

HashMap * createHashMap(){
    HashMap * map = (HashMap * )malloc(sizeof(HashMap));
    for(int i =0; i<MAP_SIZE; i++){
        map->bucket[i] = NULL;
    }

    return map;
}

int hash(char key){
   return key % MAP_SIZE;
}

int sizeOfMap(HashMap * map){
    return map->size;
}

void put(HashMap * map, char key, int value){
    int index = hash(key);
    Node * node = map->bucket[index];
    while(node != NULL){
        if(node->c == key){
            node->count += value;
            return;
        }

        node = node->next;
    }

    Node * newNode = createNode(key, value);
    newNode->next = map->bucket[index];
    map->bucket[index] = newNode;
    map->size ++;
    return;

}

int get(HashMap * map, char key){
    int index = hash(key);
    Node * node = map->bucket[index];
    while(node!=NULL){
        if(node->c == key){
            return node->count;
        }
        node = node->next;
    }
    return 0;
}

void delete(HashMap * map, char key){
    int index = hash(key);
    Node * node = map->bucket[index];
    Node * prev = NULL;

    while (node != NULL) {
        if (node->c == key) {
            if (prev == NULL) { 
                map->bucket[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            map->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}


int helper(char * input, int k){
    HashMap * map = createHashMap();
    int start = 0;
    int max = 0;

    for(int end = 0; end <strlen(input); end ++){
        put(map, input[end], 1);

        while(sizeOfMap(map) > k){
            put(map, input[start], -1);
            if(get(map, input[start]) == 0){
                delete(map, input[start]);
            }
            start ++;
        }

        int currSize = end - start + 1;
        if(currSize > max)
            max = currSize;
        
    }
    return max;
}

void parseInput(char * input, int * k){
    scanf("%s", input);
    getchar();
    scanf("%d", k);
    return;
}

int main(){
    int k;
    char input[max_size];
    parseInput(input, &k);

    int ans = helper(input, k);
    printf("length of longest subarray with k distinct keys is : %d\n", ans);

}