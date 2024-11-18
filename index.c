#include <stdio.h>
#include <string.h>
#include <ctype.h>

int od_top = -1, op_top = -1;
int operands_st[1000], operators_st[1000];

int isOperand(char ch) {
    return (ch >= '0' && ch <= '9');
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int evaluate() {
    int op2 = operands_st[od_top--];
    int op1 = operands_st[od_top--];
    char op = operators_st[op_top--];

    switch(op) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': if(op2 == 0) return -2; return op1 / op2;
    }
    return 0;
}

int precedence(char op1, char op2) {
    int precedence[256] = {0}; 
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;

    if (precedence[(unsigned char)op1] == 0 || precedence[(unsigned char)op2] == 0) {
        return -1; 
    }

    if (precedence[(unsigned char)op1] == precedence[(unsigned char)op2]) {
        return 0;
    }
    return (precedence[(unsigned char)op1] > precedence[(unsigned char)op2]) ? 1 : -1;
}

int parse_expression(char expression[]) {
    int i = 0;
    while (i < strlen(expression)) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (isOperand(expression[i]) || (expression[i] == '-' && (i == 0 || isOperator(expression[i - 1]) || isspace(expression[i - 1])))) {
            int num = 0;
            int sign = 1;
            if (expression[i] == '-') {
                sign = -1;
                i++;
            }
            while (i < strlen(expression) && isOperand(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            operands_st[++od_top] = num * sign;
        } else if (isOperator(expression[i])) {
            while (op_top != -1 && precedence(expression[i], operators_st[op_top]) <= 0) {
                int result = evaluate();
                if (result == -2) {
                    return -2;
                }
                operands_st[++od_top] = result;
            }
            operators_st[++op_top] = expression[i];
            i++;
        } else {
            return -1;
        }
    }

    while (op_top != -1) {
        int result = evaluate();
        if (result == -2) {
            return -2;
        }
        operands_st[++od_top] = result;
    }
    return 0;
}

int main() {
    char expression[2000];
    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin);

    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }

    if (strlen(expression) == 0) {
        printf("You entered an empty string\n");
        return 0;
    }

    int res = parse_expression(expression);

    if (res == -1) {
        printf("Error: Invalid expression\n");
    } else if (res == -2) {
        printf("Error: Division by zero\n");
    } else {
        printf("Result is: %d\n", operands_st[od_top]);
    }

    return 0;
}