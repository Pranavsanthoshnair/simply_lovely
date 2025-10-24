#include <stdio.h>

struct Term {
    int coeff, expo;
};

void addPoly(struct Term p1[], int n1, struct Term p2[], int n2, struct Term res[], int *nRes) {
    int i = 0, j = 0, k = 0;
    
    // Compare and merge
    while (i < n1 && j < n2) {
        if (p1[i].expo == p2[j].expo) {
            res[k].coeff = p1[i].coeff + p2[j].coeff;
            res[k].expo = p1[i].expo;
            i++; j++; k++;
        }
        else if (p1[i].expo > p2[j].expo) {
            res[k] = p1[i];
            i++; k++;
        }
        else {
            res[k] = p2[j];
            j++; k++;
        }
    }
    
    while (i < n1) res[k++] = p1[i++];
    while (j < n2) res[k++] = p2[j++];
    
    *nRes = k;
}

void display(struct Term p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%dx^%d", p[i].coeff, p[i].expo);
        if (i != n - 1) printf(" + ");
    }
    printf("\n");
}

void read(struct Term p[], int *n) {
    printf("Enter number of terms: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("Term %d (coeff expo): ", i + 1);
        scanf("%d %d", &p[i].coeff, &p[i].expo);
    }
}

int main() {
    struct Term p1[20], p2[20], res[40];
    int n1, n2, nRes;
    
    printf("First Polynomial:\n");
    read(p1, &n1);
    
    printf("\nSecond Polynomial:\n");
    read(p2, &n2);
    
    printf("\nP1: ");
    display(p1, n1);
    
    printf("P2: ");
    display(p2, n2);
    
    addPoly(p1, n1, p2, n2, res, &nRes);
    
    printf("Sum: ");
    display(res, nRes);
    
    return 0;
}
