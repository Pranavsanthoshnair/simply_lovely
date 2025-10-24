#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node *left, *right;
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void toPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1, k = 0;
    
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        }
        else if (infix[i] == '(') {
            stack[++top] = infix[i];
        }
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--;
        }
        else {
            while (top != -1 && precedence(infix[i]) <= precedence(stack[top]))
                postfix[k++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    
    while (top != -1)
        postfix[k++] = stack[top--];
    
    postfix[k] = '\0';
}

struct Node* createNode(char c) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

struct Node* buildTree(char* postfix) {
    struct Node* stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i]; i++) {
        struct Node* node = createNode(postfix[i]);
        
        if (isalnum(postfix[i])) {
            stack[++top] = node;
        }
        else {
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    
    return stack[top];
}

void showTree(struct Node* root, char* prefix, int isLeft) {
    if (root == NULL) return;
    
    printf("%s%s%c\n", prefix, isLeft ? "├──" : "└──", root->data);
    
    char newPrefix[100];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLeft ? "│   " : "    ");
    
    if (root->left || root->right) {
        showTree(root->left, newPrefix, 1);
        showTree(root->right, newPrefix, 0);
    }
}

void prefix(struct Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    prefix(root->left);
    prefix(root->right);
}

int main() {
    char infix[100], postfix[100];
    
    printf("Enter infix expression: ");
    fgets(infix, 100, stdin);
    infix[strcspn(infix, "\n")] = 0;
    
    toPostfix(infix, postfix);
    struct Node* root = buildTree(postfix);
    
    printf("\nInfix  : %s", infix);
    printf("\nPostfix: %s", postfix);
    printf("\nPrefix : ");
    prefix(root);
    printf("\n\nTree:\n");
    showTree(root, "", 0);
    
    return 0;
}
