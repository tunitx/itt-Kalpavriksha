#include<stdio.h>
#include<string.h>
#define MAX_ROWS 10
#define MAX_COLS 101
#define MIN_ROWS 1
#define MIN_COLS 1

int isVowel(char curr_character){
    return (curr_character == 'a' || curr_character == 'e' || curr_character == 'i' || curr_character == 'o' || curr_character == 'u' || curr_character == 'A' || curr_character == 'E' || curr_character == 'I' || curr_character == 'O' || curr_character == 'U') ? 1 : 0;
}

int main(){
    int rows, cols;
    printf("Enter the rows and columns within the range 1<=rows<=10 and 1<=cols<=101: ");
    while(scanf("%d %d", &rows, &cols) != 2 || rows < MIN_ROWS || cols < MIN_COLS || rows > MAX_ROWS || cols > MAX_COLS){
        printf("Invalid input, please follow range 1<=rows<=10 and 1<=cols<=101: ");
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
            if(isVowel(mat[i][j][0])){
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