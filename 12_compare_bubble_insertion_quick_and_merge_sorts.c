#include <stdio.h>

int bubbleSteps = 0, insertionSteps = 0, mergeSteps = 0, quickSteps = 0;

void bubbleSort(int A[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int t = A[j];
                A[j] = A[j + 1];
                A[j + 1] = t;
            }
            bubbleSteps++;
        }
}

void insertionSort(int B[], int n) {
    for (int i = 1; i < n; i++) {
        int key = B[i], j = i - 1;
        while (j >= 0 && B[j] > key) {
            B[j + 1] = B[j];
            j--;
            insertionSteps++;
        }
        B[j + 1] = key;
    }
}

void mergeSort(int C[], int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        mergeSort(C, lb, mid);
        mergeSort(C, mid + 1, ub);

        int i = lb, j = mid + 1, k = lb;
        int D[100];
        while (i <= mid && j <= ub) {
            mergeSteps++;
            if (C[i] <= C[j]) D[k++] = C[i++];
            else D[k++] = C[j++];
        }
        while (i <= mid) D[k++] = C[i++];
        while (j <= ub) D[k++] = C[j++];
        for (int x = lb; x <= ub; x++) C[x] = D[x];
    }
}

void quickSort(int E[], int low, int high) {
    if (low < high) {
        int pivot = E[high], i = low;
        for (int j = low; j < high; j++)
            if (E[j] <= pivot) {
                int t = E[i];
                E[i] = E[j];
                E[j] = t;
                quickSteps++;
                i++;
            }
        int t = E[i];
        E[i] = E[high];
        E[high] = t;
        quickSteps++;

        int p = i;
        quickSort(E, low, p - 1);
        quickSort(E, p + 1, high);
    }
}

int main() {
    int n, A[100], B[100], C[100], E[100];
    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        B[i] = C[i] = E[i] = A[i];
    }

    bubbleSort(A, n);
    insertionSort(B, n);
    mergeSort(C, 0, n - 1);
    quickSort(E, 0, n - 1);

    printf("\nBubble: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf(" Steps=%d", bubbleSteps);

    printf("\nInsertion: ");
    for (int i = 0; i < n; i++) printf("%d ", B[i]);
    printf(" Steps=%d", insertionSteps);

    printf("\nMerge: ");
    for (int i = 0; i < n; i++) printf("%d ", C[i]);
    printf(" Steps=%d", mergeSteps);

    printf("\nQuick: ");
    for (int i = 0; i < n; i++) printf("%d ", E[i]);
    printf(" Steps=%d\n", quickSteps);

    return 0;
}
