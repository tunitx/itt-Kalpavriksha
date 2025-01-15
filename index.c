// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("enter the size of N*N matrix: ");
    scanf("%d", &n);
    
    int ** mat = (int **)malloc(n * sizeof(int *));
    for(int i =0; i<n; i++){
        mat[i] = (int *)malloc(n*sizeof(int));
    }
    
    printf("enter the elements of the matrix: \n");
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    
    for(int i =0; i<n; i++){
        for(int j =i+1; j<n; j++){
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
    printf("the transposed matrix is : \n");
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    for(int i =0; i<n; i++){
        free(mat[i]);
    }
    free(mat);
    return 0;
}