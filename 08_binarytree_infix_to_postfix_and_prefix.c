#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node *left, *right;
};

void inorder(struct Node *root) {
    if (root == NULL) return;
    if (root->left || root->right) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if (root->left || root->right) printf(")");
}

void preorder(struct Node *root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

void showTree(struct Node *root, int level) {
    if (root == NULL) return;

    showTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%c\n", root->data);

    showTree(root->left, level + 1);
}

int main() {
    char infix[100], postfix[100], opstack[100];
    struct Node *nodestack[100];
    int topOp = -1, topNode = -1, j = 0;

    printf("Enter infix expression (single-letter/ digit operands): ");
    scanf("%s", infix);

    // INFIX TO POSTFIX (style similar to your reference code)
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            opstack[++topOp] = ch;
        }
        else if (ch == ')') {
            while (topOp != -1 && opstack[topOp] != '(') {
                postfix[j++] = opstack[topOp--];
            }
            topOp--; // pop '('
        }
        else { // operator
            int p1;
            if (ch == '+' || ch == '-') p1 = 1;
            else if (ch == '*' || ch == '/') p1 = 2;
            else if (ch == '^') p1 = 3;
            else p1 = 0;

            while (topOp != -1) {
                char op = opstack[topOp];
                int p2;
                if (op == '+' || op == '-') p2 = 1;
                else if (op == '*' || op == '/') p2 = 2;
                else if (op == '^') p2 = 3;
                else p2 = 0;

                if (p2 > p1 || (p2 == p1 && ch != '^')) {
                    postfix[j++] = opstack[topOp--];
                } else break;
            }
            opstack[++topOp] = ch;
        }
    }

    while (topOp != -1) {
        postfix[j++] = opstack[topOp--];
    }
    postfix[j] = '\0';

    // BUILD EXPRESSION TREE FROM POSTFIX
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        struct Node *node = (struct Node *)malloc(sizeof(struct Node));
        node->data = ch;
        node->left = node->right = NULL;

        if (isalnum(ch)) {
            nodestack[++topNode] = node;
        } else { // operator
            node->right = nodestack[topNode--];
            node->left  = nodestack[topNode--];
            nodestack[++topNode] = node;
        }
    }

    struct Node *root = nodestack[topNode];

    printf("\nInfix   : %s\n", infix);
    printf("Postfix : %s\n", postfix);

    printf("Inorder (infix)   : ");
    inorder(root);
    printf("\n");

    printf("Preorder (prefix) : ");
    preorder(root);
    printf("\n");

    printf("Postorder(postfix): ");
    postorder(root);
    printf("\n");

    printf("\nExpression Tree (rotated 90 degrees):\n");
    showTree(root, 0);

    return 0;
}
