#include <stdio.h>

int q[100], front = -1, rear = -1, size, type;

int isFull() {
    if (type == 1) return rear == size - 1;
    return (rear + 1) % size == front;
}

int isEmpty() {
    return front == -1;
}

void display() {
    if (isEmpty()) {
        printf("Queue empty\n");
        return;
    }
    printf("Queue: ");
    if (type == 1) {
        for (int i = front; i <= rear; i++)
            printf("%d ", q[i]);
    } else {
        int i = front;
        while (1) {
            printf("%d ", q[i]);
            if (i == rear) break;
            i = (i + 1) % size;
        }
    }
    printf("\n");
}

void enqueue(int val) {
    if (isFull()) {
        printf("Queue full\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else {
        if (type == 1) rear++;
        else rear = (rear + 1) % size;
    }
    q[rear] = val;
    printf("%d inserted\n", val);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue empty\n");
        return;
    }
    printf("Deleted: %d\n", q[front]);
    if (front == rear) {
        front = rear = -1;
    } else {
        if (type == 1) front++;
        else front = (front + 1) % size;
    }
}

void insertFront(int val) {
    if (isFull()) {
        printf("Deque full\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else {
        front = (front - 1 + size) % size;
    }
    q[front] = val;
    printf("%d inserted at front\n", val);
}

void deleteRear() {
    if (isEmpty()) {
        printf("Deque empty\n");
        return;
    }
    printf("Deleted: %d\n", q[rear]);
    if (front == rear) {
        front = rear = -1;
    } else {
        rear = (rear - 1 + size) % size;
    }
}

int main() {
    int choice, val;
    
    printf("Select Queue Type:\n");
    printf("1. Simple Queue\n");
    printf("2. Circular Queue\n");
    printf("3. Deque\n");
    printf("Choice: ");
    scanf("%d", &type);
    
    printf("Enter size (max 100): ");
    scanf("%d", &size);
    
    while (1) {
        if (type == 3) {
            printf("\n1.Insert Front 2.Insert Rear 3.Delete Front 4.Delete Rear 5.Exit\n");
        } else {
            printf("\n1.Enqueue 2.Dequeue 3.Exit\n");
        }
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (type == 3) {
            if (choice == 1) {
                printf("Value: ");
                scanf("%d", &val);
                insertFront(val);
                display();
            }
            else if (choice == 2) {
                printf("Value: ");
                scanf("%d", &val);
                enqueue(val);
                display();
            }
            else if (choice == 3) {
                dequeue();
                display();
            }
            else if (choice == 4) {
                deleteRear();
                display();
            }
            else if (choice == 5) break;
        } else {
            if (choice == 1) {
                printf("Value: ");
                scanf("%d", &val);
                enqueue(val);
                display();
            }
            else if (choice == 2) {
                dequeue();
                display();
            }
            else if (choice == 3) break;
        }
    }
    
    return 0;
}
