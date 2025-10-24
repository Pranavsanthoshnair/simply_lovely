#include <stdio.h>

int q[100], front = -1, rear = -1, size;

void display() {
    if (front == -1) {
        printf("Queue empty\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", q[i]);
        if (i == rear) break;
        i = (i + 1) % size;
    }
    printf("\n");
}

void enqueue(int val) {
    if ((rear + 1) % size == front) {
        printf("Queue full\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % size;
    }
    q[rear] = val;
    printf("%d inserted\n", val);
    display();
}

void dequeue() {
    if (front == -1) {
        printf("Queue empty\n");
        return;
    }
    printf("Deleted: %d\n", q[front]);
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % size;
    }
    display();
}

int main() {
    int choice, val;
    
    printf("Enter size (max 100): ");
    scanf("%d", &size);
    
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Exit\nChoice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("Value: ");
            scanf("%d", &val);
            enqueue(val);
        }
        else if (choice == 2) {
            dequeue();
        }
        else if (choice == 3) {
            break;
        }
    }
    
    return 0;
}
