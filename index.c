#include<stdio.h>
#include<string.h>

int is_vowel(char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') ? 1 : 0;
}

int main(){
    int rows, cols;
    printf("enter the rows and columns: ");
    while(scanf("%d %d", &rows, &cols) != 2){
        printf("Invalid input. Please enter again: ");
        while(getchar() != '\n');
    }
    
    char mat[rows][cols][51];

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
            printf("Enter the element at (%d %d) : ", i, j);
            scanf("%s", mat[i][j]);
        }
    }

    printf("\n");

    int words_with_vowel = 0, max_len = 0, cord_x, cord_y;

    for(int i =0; i<rows; i++){
        for(int j =0; j<cols; j++){
            printf("%s ", mat[i][j]);
            if(is_vowel(mat[i][j][0])){
                words_with_vowel++;
            }
            int curr_len = strlen(mat[i][j]);
            if(curr_len > max_len){
                max_len = curr_len;
                cord_x = i;
                cord_y = j;
            }
        }
        printf("\n");
    }

    printf("Number of words starting with a vowel: %d\n", words_with_vowel);
    printf("Length of the longest word: %s\n", mat[cord_x][cord_y]);

    return 0;


}