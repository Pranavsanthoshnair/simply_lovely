#include <stdio.h>

int steps;

void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copy(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void bubbleSort(int arr[], int n) {
    steps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            steps++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    steps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            steps++;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        steps++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        steps++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    printf("Number of elements: ");
    scanf("%d", &n);
    int arr[n], temp[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    copy(arr, temp, n);
    bubbleSort(temp, n);
    printf("\nBubble Sort: ");
    print(temp, n);
    int bubbleSteps = steps;
    
    copy(arr, temp, n);
    insertionSort(temp, n);
    printf("Insertion Sort: ");
    print(temp, n);
    int insertionSteps = steps;
    
    copy(arr, temp, n);
    steps = 0;
    quickSort(temp, 0, n - 1);
    printf("Quick Sort: ");
    print(temp, n);
    int quickSteps = steps;
    
    copy(arr, temp, n);
    steps = 0;
    mergeSort(temp, 0, n - 1);
    printf("Merge Sort: ");
    print(temp, n);
    int mergeSteps = steps;
    
    printf("\nSteps:\n");
    printf("Bubble: %d\n", bubbleSteps);
    printf("Insertion: %d\n", insertionSteps);
    printf("Quick: %d\n", quickSteps);
    printf("Merge: %d\n", mergeSteps);
    
    return 0;
}
