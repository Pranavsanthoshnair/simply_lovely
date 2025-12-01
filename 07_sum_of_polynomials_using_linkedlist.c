#include <stdio.h>
#include <stdlib.h>

typedef struct Polynomial {
    int coeff;
    int expo;
    struct Polynomial *next;
} Polynomial;

int main() {
    int n1, n2, coeff, expo;
    Polynomial *poly1 = NULL, *poly2 = NULL, *result = NULL;
    Polynomial *temp = NULL, *ptr = NULL;
    
    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n1);

    printf("Enter coeff and expo for first polynomial:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d %d", &coeff, &expo);
        temp = (Polynomial *)malloc(sizeof(Polynomial));
        temp->coeff = coeff;
        temp->expo = expo;
        temp->next = NULL;

        if (poly1 == NULL)
            poly1 = temp;
        else {
            ptr = poly1;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = temp;
        }
    }

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n2);

    printf("Enter coeff and expo for second polynomial:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d %d", &coeff, &expo);
        temp = (Polynomial *)malloc(sizeof(Polynomial));
        temp->coeff = coeff;
        temp->expo = expo;
        temp->next = NULL;

        if (poly2 == NULL)
            poly2 = temp;
        else {
            ptr = poly2;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = temp;
        }
    }

    Polynomial *p1 = poly1, *p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        temp = (Polynomial *)malloc(sizeof(Polynomial));
        temp->next = NULL;

        if (p1->expo == p2->expo) {
            temp->expo = p1->expo;
            temp->coeff = p1->coeff + p2->coeff;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->expo > p2->expo) {
            temp->expo = p1->expo;
            temp->coeff = p1->coeff;
            p1 = p1->next;
        }
        else {
            temp->expo = p2->expo;
            temp->coeff = p2->coeff;
            p2 = p2->next;
        }

        if (result == NULL)
            result = temp;
        else {
            ptr = result;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = temp;
        }
    }

    while (p1 != NULL) {
        temp = (Polynomial *)malloc(sizeof(Polynomial));
        temp->coeff = p1->coeff;
        temp->expo = p1->expo;
        temp->next = NULL;

        if (result == NULL)
            result = temp;
        else {
            ptr = result;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = temp;
        }
        p1 = p1->next;
    }

    while (p2 != NULL) {
        temp = (Polynomial *)malloc(sizeof(Polynomial));
        temp->coeff = p2->coeff;
        temp->expo = p2->expo;
        temp->next = NULL;

        if (result == NULL)
            result = temp;
        else {
            ptr = result;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = temp;
        }
        p2 = p2->next;
    }

    printf("Sum:\n");
    ptr = result;
    while (ptr != NULL) {
        printf("%dx^%d", ptr->coeff, ptr->expo);
        ptr = ptr->next;
        if (ptr != NULL)
            printf(" + ");
    }

    return 0;
}
