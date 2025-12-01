#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("Enter no of vertices: ");
    scanf("%d", &n);

    int queue[100], rear = 0, front = 0;
    int matrix[100][100], visited[100];
    char vertices[100][20], startingvertex[20];

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Enter vertex names:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", vertices[i]);
    }

    printf("Enter starting vertex: ");
    scanf("%s", startingvertex);

    int startingindex = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(vertices[i], startingvertex) == 0) {
            startingindex = i;
            break;
        }
    }

    if (startingindex == -1) {
        printf("Invalid vertex!\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    queue[rear++] = startingindex;
    visited[startingindex] = 1;

    printf("\nBFS: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%s ", vertices[current]);
        for (int i = 0; i < n; i++) {
            if (matrix[current][i] == 1 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
    return 0;
}
