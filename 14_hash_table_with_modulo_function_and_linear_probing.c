#include <stdio.h>
#define SIZE 10

int main() {
    int table[SIZE];
    int i, n, value;
    
    for (i = 0; i < SIZE; i++)
        table[i] = -1;
    
    printf("Number of elements: ");
    scanf("%d", &n);
    
    printf("Enter elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        int index = value % SIZE;
        
        // Linear probing for collision
        while (table[index] != -1) {
            index = (index + 1) % SIZE;
        }
        table[index] = value;
    }
    
    printf("\nHash Table:\n");
    for (i = 0; i < SIZE; i++) {
        if (table[i] != -1)
            printf("%d : %d\n", i, table[i]);
        else
            printf("%d : ---\n", i);
    }
    
    return 0;
}
