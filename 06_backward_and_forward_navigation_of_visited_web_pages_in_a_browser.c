#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char url[100];
    struct Node *prev, *next;
} Node;

Node *current = NULL;

void visit(char *url) {
    Node *newPage = (Node *)malloc(sizeof(Node));
    strcpy(newPage->url, url);
    newPage->prev = current;
    newPage->next = NULL;
    
    if (current) {
        Node *temp = current->next;
        while (temp) {
            Node *del = temp;
            temp = temp->next;
            free(del);
        }
        current->next = newPage;
    }
    
    current = newPage;
    printf("Visited: %s\n", url);
}

void back() {
    if (current && current->prev) {
        current = current->prev;
        printf("Back to: %s\n", current->url);
    } else {
        printf("No previous page\n");
    }
}

void forward() {
    if (current && current->next) {
        current = current->next;
        printf("Forward to: %s\n", current->url);
    } else {
        printf("No forward page\n");
    }
}

void show() {
    if (current) {
        printf("Current: %s\n", current->url);
    } else {
        printf("No page open\n");
    }
}

int main() {
    int choice;
    char url[100];
    
    while (1) {
        printf("\n1.Visit 2.Back 3.Forward 4.Current 5.Exit\nChoice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("URL: ");
            scanf("%s", url);
            visit(url);
        }
        else if (choice == 2) back();
        else if (choice == 3) forward();
        else if (choice == 4) show();
        else if (choice == 5) break;
    }
    
    return 0;
}
