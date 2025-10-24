#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, k = 0;
    top = -1;
    
    while (infix[i]) {
        char c = infix[i];
        
        if (isspace(c)) {
            i++;
            continue;
        }
        
        if (isalnum(c)) {
            postfix[k++] = c;
            postfix[k++] = ' ';
            i++;
        }
        else if (c == '(') {
            push(c);
            i++;
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            pop();
            i++;
        }
        else if (isOperator(c)) {
            // Pop operators with higher or equal precedence
            while (top != -1 && stack[top] != '(' && 
                   precedence(stack[top]) >= precedence(c) &&
                   !(c == '^' && stack[top] == '^')) {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            push(c);
            i++;
        }
        else {
            i++;
        }
    }
    
    while (top != -1) {
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }
    
    postfix[k] = '\0';
}

float power(float base, int exp) {
    float res = 1;
    for (int i = 0; i < exp; i++)
        res *= base;
    return res;
}

int hasVariable(char *expr) {
    for (int i = 0; expr[i]; i++)
        if (isalpha(expr[i]))
            return 1;
    return 0;
}

float evaluatePostfix(char *postfix) {
    float s[MAX];
    int t = -1;
    int i = 0;
    
    while (postfix[i]) {
        if (isspace(postfix[i])) {
            i++;
            continue;
        }
        
        if (isdigit(postfix[i])) {
            s[++t] = postfix[i] - '0';
            i++;
        }
        else if (isOperator(postfix[i])) {
            float b = s[t--];
            float a = s[t--];
            
            if (postfix[i] == '+') s[++t] = a + b;
            else if (postfix[i] == '-') s[++t] = a - b;
            else if (postfix[i] == '*') s[++t] = a * b;
            else if (postfix[i] == '/') s[++t] = a / b;
            else if (postfix[i] == '^') s[++t] = power(a, (int)b);
            
            i++;
        }
        else {
            i++;
        }
    }
    
    return s[t];
}

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0;
    
    infixToPostfix(infix, postfix);
    
    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);
    
    if (hasVariable(infix))
        printf("Contains variables, can't evaluate.\n");
    else {
        float result = evaluatePostfix(postfix);
        printf("Result: %.2f\n", result);
    }
    
    return 0;
}
