#include <stdio.h>

typedef struct {
    int row, col, val;
} Element;

int size;
int A[10][10], B[10][10];
Element cA[100], cB[100], cSum[200], cTrans[200];

void inputMatrix(int M[10][10]) {
    int n, r, c, v;
    printf("Enter number of non-zero elements: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter row col value: ");
        scanf("%d %d %d", &r, &c, &v);
        M[r][c] = v;
    }
}

int toCompact(int M[10][10], Element C[100]) {
    int k = 1;
    C[0].row = size;
    C[0].col = size;
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (M[i][j] != 0) {
                C[k].row = i;
                C[k].col = j;
                C[k].val = M[i][j];
                k++;
            }
    
    C[0].val = k - 1;
    return k - 1;
}

int addCompact(Element A[100], Element B[100], Element R[200]) {
    int i = 1, j = 1, k = 1;
    R[0].row = size;
    R[0].col = size;
    
    // Merge sorted lists
    while (i <= A[0].val && j <= B[0].val) {
        if (A[i].row < B[j].row || (A[i].row == B[j].row && A[i].col < B[j].col)) {
            R[k++] = A[i++];
        }
        else if (B[j].row < A[i].row || (B[j].row == A[i].row && B[j].col < A[i].col)) {
            R[k++] = B[j++];
        }
        else {
            R[k].row = A[i].row;
            R[k].col = A[i].col;
            R[k].val = A[i].val + B[j].val;
            k++; i++; j++;
        }
    }
    
    while (i <= A[0].val) R[k++] = A[i++];
    while (j <= B[0].val) R[k++] = B[j++];
    
    R[0].val = k - 1;
    return k - 1;
}

void toMatrix(Element C[200], int M[10][10]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            M[i][j] = 0;
    
    for (int i = 1; i <= C[0].val; i++)
        M[C[i].row][C[i].col] = C[i].val;
}

void transpose(Element S[200], Element T[200]) {
    T[0].row = S[0].col;
    T[0].col = S[0].row;
    T[0].val = S[0].val;
    int k = 1;
    
    for (int i = 0; i < size; i++)
        for (int j = 1; j <= S[0].val; j++)
            if (S[j].col == i) {
                T[k].row = S[j].col;
                T[k].col = S[j].row;
                T[k].val = S[j].val;
                k++;
            }
}

void showMatrix(int M[10][10]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%3d ", M[i][j]);
        printf("\n");
    }
}

void showCompact(Element C[200]) {
    printf("Row Col Val\n");
    for (int i = 0; i <= C[0].val; i++)
        printf("%3d %3d %3d\n", C[i].row, C[i].col, C[i].val);
}

int main() {
    printf("Enter matrix size: ");
    scanf("%d", &size);
    
    printf("\nMatrix A:\n");
    inputMatrix(A);
    printf("\nMatrix B:\n");
    inputMatrix(B);
    
    toCompact(A, cA);
    toCompact(B, cB);
    
    int choice;
    while (1) {
        printf("\n1.Add 2.Transpose 3.Show A 4.Show B 5.Exit\n");
        scanf("%d", &choice);
        
        if (choice == 1) {
            addCompact(cA, cB, cSum);
            int sum[10][10];
            toMatrix(cSum, sum);
            printf("\nSum:\n");
            showMatrix(sum);
        }
        else if (choice == 2) {
            if (cSum[0].val > 0) {
                transpose(cSum, cTrans);
                printf("\nTranspose:\n");
                showCompact(cTrans);
            }
        }
        else if (choice == 3) {
            printf("\nMatrix A:\n");
            showMatrix(A);
            showCompact(cA);
        }
        else if (choice == 4) {
            printf("\nMatrix B:\n");
            showMatrix(B);
            showCompact(cB);
        }
        else if (choice == 5) break;
    }
    
    return 0;
}
