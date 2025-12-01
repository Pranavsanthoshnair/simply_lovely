#include <stdio.h>

int main() {
    int n, target;

    printf("Enter size of sorted array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &target);

    int low = 0, high = n - 1;
    int foundIndex = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            foundIndex = mid;
            break;
        } 
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    if (foundIndex == -1)
        printf("Element not found.\n");
    else
        printf("Element found at index %d\n", foundIndex);

    printf("Time complexity: O(log n)\nSpace complexity: O(1)\n");

    return 0;
}
