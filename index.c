#include <stdio.h>
#include <string.h>
#include <ctype.h>

//? changed the max to maxLength.

#define maxLength 300

//? improved naming of operator stack, number stack, their push & pop operations & their tops.

char operatorStack[maxLength];
int operatorStackTop = -1;

int numberStack[maxLength];
int numStackTop = -1;

void pushOperator(char op) {
    operatorStack[++operatorStackTop] = op;
}

char popOperator() {
    return operatorStack[operatorStackTop--];
}

void pushNumber(int val) {
    numberStack[++numStackTop] = val;
}

int popNumber() {
    return numberStack[numStackTop--];
}

//? changed the multiple return statements to single ternary op based condition

int getOperatorPrecedence(char op) {
 return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

int isMathOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int convertToPostfix(char infix[], char postfix[]) {
    int index = 0, postIndex = 0;
    int expectNum = 1;

    while (infix[index] != '\0') {
        if (infix[index] == ' ') {
            index++;
            continue;
        }

        if (isdigit(infix[index]) || (infix[index] == '-' && isdigit(infix[index + 1]) && expectNum)) {
            if (!expectNum) return -1;

            int sign = 1;
            if (infix[index] == '-') {
                sign = -1;
                index++;
            }

            int value = 0;
            while (isdigit(infix[index])) {
                value = value * 10 + (infix[index++] - '0');
            }
            value *= sign;

            if (value < 0) {
                postfix[postIndex++] = '-';
                value = -value;
            }

            char temp[20];
            int len = 0;
            do {
                temp[len++] = (value % 10) + '0';
                value /= 10;
            } while (value > 0);

            for (int k = len - 1; k >= 0; k--) {
                postfix[postIndex++] = temp[k];
            }
            postfix[postIndex++] = ' ';

            expectNum = 0;
        } else if (isMathOperator(infix[index])) {
            if (expectNum) return -1;

            while (operatorStackTop != -1 && getOperatorPrecedence(operatorStack[operatorStackTop]) >= getOperatorPrecedence(infix[index])) {
                postfix[postIndex++] = popOperator();
                postfix[postIndex++] = ' ';
            }

            pushOperator(infix[index]);
            index++;
            expectNum = 1;
        } else {
            return -1;
        }
    }

    if (expectNum) return -1;

    while (operatorStackTop != -1) {
        postfix[postIndex++] = popOperator();
        postfix[postIndex++] = ' ';
    }
    postfix[postIndex] = '\0';
    return 0;
}

int calculatePostfix(char postfix[], int *hasError) {
    int index = 0;

    while (postfix[index] != '\0') {
        if (isdigit(postfix[index]) || (postfix[index] == '-' && isdigit(postfix[index + 1]))) {
            int value = 0, sign = 1;

            if (postfix[index] == '-') {
                sign = -1;
                index++;
            }

            while (isdigit(postfix[index])) {
                value = value * 10 + (postfix[index++] - '0');
            }
            pushNumber(sign * value);
        } else if (isMathOperator(postfix[index])) {
            if (numStackTop < 1) {
                *hasError = 1;
                return 0;
            }

            int right = popNumber();
            int left = popNumber();

            if (postfix[index] == '/' && right == 0) {
                *hasError = 2;
                return 0;
            }

            switch (postfix[index]) {
                case '+': pushNumber(left + right); break;
                case '-': pushNumber(left - right); break;
                case '*': pushNumber(left * right); break;
                case '/': pushNumber(left / right); break;
            }
            index++;
        } else {
            index++;
        }
    }

    return popNumber();
}

int main() {
    char input[maxLength];
    char output[maxLength];

    printf("Enter an expression: ");
    if (fgets(input, maxLength, stdin)) {
        input[strcspn(input, "\n")] = '\0';
    }

    int isEmpty = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            isEmpty = 0;
            break;
        }
    }

    if (isEmpty) {
        printf("Error: Expression cannot be blank\n");
        return 0;
    }

    int status = convertToPostfix(input, output);
    if (status == -1) {
        printf("Error: Invalid expression\n");
        return 0;
    }

    //? removed postfix exp printing line

    int errorFlag = 0;
    int result = calculatePostfix(output, &errorFlag);

    if (errorFlag == 1) {
        printf("Error: Invalid postfix expression\n");
    } else if (errorFlag == 2) {
        printf("Error: Division by zero\n");
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}
