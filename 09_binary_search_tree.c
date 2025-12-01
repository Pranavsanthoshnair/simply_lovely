#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* insertNode(Node* root, int value) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    return root;
}

Node* searchNode(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert  2. Delete  3. Search  4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Value: ");
            scanf("%d", &value);
            root = insertNode(root, value);
            printf("Tree (inorder): ");
            inorder(root);
            printf("\n");
        }
        else if (choice == 2) {
            printf("Value: ");
            scanf("%d", &value);
            if (searchNode(root, value) != NULL) {
                root = deleteNode(root, value);
                printf("Deleted\n");
            } else {
                printf("Not found\n");
            }
            printf("Tree (inorder): ");
            inorder(root);
            printf("\n");
        }
        else if (choice == 3) {
            printf("Value: ");
            scanf("%d", &value);
            if (searchNode(root, value) != NULL)
                printf("Found\n");
            else
                printf("Not found\n");
        }
        else if (choice == 4) {
            exit(0);
        }
    }

    return 0;
}
