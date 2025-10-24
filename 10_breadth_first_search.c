#include <stdio.h>
#include <string.h>
#define MAX 100

int queue[MAX], front = 0, rear = 0;
int visited[MAX];
char vertices[MAX][10];

void enqueue(int value) {
    queue[rear++] = value;
}

int dequeue() {
    return queue[front++];
}

int getIndex(char name[], int n) {
    for (int i = 0; i < n; i++)
        if (strcmp(vertices[i], name) == 0) 
            return i;
    return -1;
}

void bfs(int adj[MAX][MAX], int start, int n) {
    enqueue(start);
    visited[start] = 1;
    printf("\nBFS: ");
    while (front < rear) {
        int current = dequeue();
        printf("%s ", vertices[current]);
        for (int i = 0; i < n; i++)
            if (adj[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
    }
    printf("\n");
}

int main() {
    int n, adj[MAX][MAX];
    char startName[10];
    printf("Number of vertices: ");
    scanf("%d", &n);
    printf("Vertex names: ");
    for (int i = 0; i < n; i++)
        scanf("%s", vertices[i]);
    printf("\nAdjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
    printf("\nStart vertex: ");
    scanf("%s", startName);
    int startIndex = getIndex(startName, n);
    if (startIndex == -1) {
        printf("Invalid vertex!\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    bfs(adj, startIndex, n);
    return 0;
}
