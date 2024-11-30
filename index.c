#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 300

char opStack[MAX];
int opTop = -1;

int numStack[MAX];
int numTop = -1;

void pushOp(char op) {
    opStack[++opTop] = op;
}

char popOp() {
    return opStack[opTop--];
}

void pushNum(int val) {
    numStack[++numTop] = val;
}

int popNum() {
    return numStack[numTop--];
}

int opPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isMathOp(char ch) {
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
        } else if (isMathOp(infix[index])) {
            if (expectNum) return -1;

            while (opTop != -1 && opPriority(opStack[opTop]) >= opPriority(infix[index])) {
                postfix[postIndex++] = popOp();
                postfix[postIndex++] = ' ';
            }

            pushOp(infix[index]);
            index++;
            expectNum = 1;
        } else {
            return -1;
        }
    }

    if (expectNum) return -1;

    while (opTop != -1) {
        postfix[postIndex++] = popOp();
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
            pushNum(sign * value);
        } else if (isMathOp(postfix[index])) {
            if (numTop < 1) {
                *hasError = 1;
                return 0;
            }

            int right = popNum();
            int left = popNum();

            if (postfix[index] == '/' && right == 0) {
                *hasError = 2;
                return 0;
            }

            switch (postfix[index]) {
                case '+': pushNum(left + right); break;
                case '-': pushNum(left - right); break;
                case '*': pushNum(left * right); break;
                case '/': pushNum(left / right); break;
            }
            index++;
        } else {
            index++;
        }
    }

    return popNum();
}

int main() {
    char input[MAX];
    char output[MAX];

    printf("Enter an expression: ");
    if (fgets(input, MAX, stdin)) {
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

    printf("Postfix Expression: %s\n", output);

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
