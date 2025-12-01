#include <stdio.h>
#include <ctype.h>

int main() {
    char infix[100], postfix[200], stack[100];
    int top = -1, j = 0;

    scanf("%s", infix);

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalpha(ch)) {
            postfix[j++] = ch;
            postfix[j++] = ' ';
        }
        else if (isdigit(ch)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            top--;
        }
        else {
            int p1;
            if (ch == '+' || ch == '-') p1 = 1;
            else if (ch == '*' || ch == '/') p1 = 2;
            else if (ch == '^') p1 = 3;
            else p1 = 0;

            while (top != -1) {
                char op = stack[top];
                int p2;
                if (op == '+' || op == '-') p2 = 1;
                else if (op == '*' || op == '/') p2 = 2;
                else if (op == '^') p2 = 3;
                else p2 = 0;

                if (p2 > p1 || (p2 == p1 && ch != '^')) {
                    postfix[j++] = stack[top--];
                    postfix[j++] = ' ';
                } else break;
            }
            stack[++top] = ch;
        }
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
    printf("%s\n", postfix);

    int eval[100], etop = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (ch == ' ') continue;

        if (isdigit(ch)) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            eval[++etop] = num;
            i--;
        }
        else if (isalpha(ch)) {
            printf("Cannot evaluate expression containing variables\n");
            return 0;
        }
        else {
            int b = eval[etop--];
            int a = eval[etop--];
            int r;
            if (ch == '+') r = a + b;
            else if (ch == '-') r = a - b;
            else if (ch == '*') r = a * b;
            else if (ch == '/') r = a / b;
            else if (ch == '^') {
                r = 1;
                for (int k = 0; k < b; k++) r *= a;
            }
            eval[++etop] = r;
        }
    }

    printf("%d\n", eval[etop]);
    return 0;
}
