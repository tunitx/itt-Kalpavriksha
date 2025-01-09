#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[51];
    int count;
} HashEntry;

int compare(char *hash_name, char * name){
    int i =0, j =0;
    while(hash_name[i] != '\0' && name[j] != '\0'){
        if(hash_name[i] != name[j]) return 0;
        i++;
        j++;
    }
    if(hash_name[i]!='\0' || name[j] != '\0') return 0;
    return 1;
}

int helper(HashEntry *hashTable, int curr_size, char *name){
    for(int i =0; i<curr_size; i++){
        if(compare(hashTable[i].name, name)) return i;
    }
    return -1;
}

void copy_string(char *hash_name, char *name){
    int i =0;
    while(name[i] != '\0'){
        hash_name[i] = name[i];
        i++;
    }
    hash_name[i] = '\0';
}

int main(){
    int rows, cols;

    printf("Enter the rows and columns: ");
    scanf("%d %d", &rows, &cols);

    char ***mat = (char ***)malloc(rows * sizeof(char **));
    for(int i =0; i<rows; i++){
        mat[i] = (char **)malloc(cols * sizeof(char *));
        for(int j =0; j<cols; j++){
            mat[i][j] = (char *)malloc(51 * sizeof(char));
        }
    }

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
            printf("Enter the string at (%d %d) : ", i, j);
            scanf("%s", mat[i][j]);
        }
    }

    printf("\n");

    HashEntry *hashTable = (HashEntry *)malloc(1000 * sizeof(HashEntry));
    int curr_size = 0;

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
           int index = helper(hashTable, curr_size, mat[i][j]);
           if(index == -1){
           copy_string(hashTable[curr_size].name, mat[i][j]);
            hashTable[curr_size].count = 1;
            curr_size++;
           }
           else{
            hashTable[index].count++;
           }
        }
    }

    int duplicate = 0;

    for(int i =0; i<curr_size; i++){
        if(hashTable[i].count > 1){
            printf("%s %d\n", hashTable[i].name, hashTable[i].count);
            duplicate = 1;
        }
    }

    if(!duplicate){
        printf("No duplicates found\n");
    }

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
            free(mat[i][j]);
        }
        free(mat[i]);
    }

    free(mat);
    free(hashTable);

    return 0;
}