#include <stdio.h>

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int steps = 0;
    while (left <= right) {
        steps++;
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            printf("Found at index %d (Steps: %d)\n", mid, steps);
            return mid;
        }
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    printf("Not found (Steps: %d)\n", steps);
    return -1;
}

int main() {
    int n, target;
    printf("Number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d sorted elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Search for: ");
    scanf("%d", &target);
    binarySearch(arr, n, target);
    printf("\nTime: Best O(1), Worst O(log n)\n");
    printf("Space: O(1)\n");
    return 0;
}
