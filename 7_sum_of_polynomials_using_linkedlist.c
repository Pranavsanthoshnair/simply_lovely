#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff, expo;
    struct Term* next;
};

struct Term* insert(struct Term* poly, int c, int e) {
    struct Term* newNode = malloc(sizeof(struct Term));
    newNode->coeff = c;
    newNode->expo = e;
    newNode->next = NULL;
    
    if (poly == NULL || e > poly->expo) {
        newNode->next = poly;
        return newNode;
    }
    
    struct Term* temp = poly;
    while (temp->next != NULL && temp->next->expo >= e) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    
    return poly;
}

struct Term* create() {
    struct Term* poly = NULL;
    int n, c, e;
    
    printf("Enter number of terms: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Term %d (coeff expo): ", i + 1);
        scanf("%d %d", &c, &e);
        poly = insert(poly, c, e);
    }
    
    return poly;
}

void display(struct Term* poly) {
    if (poly == NULL) {
        printf("Empty\n");
        return;
    }
    
    while (poly != NULL) {
        printf("%dX^%d", poly->coeff, poly->expo);
        if (poly->next != NULL) printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

struct Term* add(struct Term* p1, struct Term* p2) {
    struct Term* result = NULL;
    
    while (p1 != NULL && p2 != NULL) {
        if (p1->expo == p2->expo) {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0) {
                result = insert(result, sum, p1->expo);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->expo > p2->expo) {
            result = insert(result, p1->coeff, p1->expo);
            p1 = p1->next;
        }
        else {
            result = insert(result, p2->coeff, p2->expo);
            p2 = p2->next;
        }
    }
    
    while (p1 != NULL) {
        result = insert(result, p1->coeff, p1->expo);
        p1 = p1->next;
    }
    
    while (p2 != NULL) {
        result = insert(result, p2->coeff, p2->expo);
        p2 = p2->next;
    }
    
    return result;
}

int main() {
    struct Term *p1 = NULL, *p2 = NULL, *result = NULL;
    
    printf("First Polynomial:\n");
    p1 = create();
    
    printf("\nSecond Polynomial:\n");
    p2 = create();
    
    result = add(p1, p2);
    
    printf("\nP1: ");
    display(p1);
    
    printf("P2: ");
    display(p2);
    
    printf("Sum: ");
    display(result);
    
    return 0;
}
