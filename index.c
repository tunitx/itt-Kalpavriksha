#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN  51

typedef struct{
    char name[MAX_LEN];
    int count;
} hash_entry;

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

int helper(hash_entry *hash_table, int curr_size, char *name){
    for(int i =0; i<curr_size; i++){
        if(compare(hash_table[i].name, name)) return i;
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

    hash_entry *hash_table = (hash_entry *)malloc((rows * cols) * sizeof(hash_entry));
    int curr_size = 0;

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
           int index = helper(hash_table, curr_size, mat[i][j]);
           if(index == -1){
           copy_string(hash_table[curr_size].name, mat[i][j]);
            hash_table[curr_size].count = 1;
            curr_size++;
           }
           else{
            hash_table[index].count++;
           }
        }
    }

    int duplicate = 0;

    for(int i =0; i<curr_size; i++){
        if(hash_table[i].count > 1){
            printf("%s %d\n", hash_table[i].name, hash_table[i].count);
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
    free(hash_table);

    return 0;
}