#include <stdio.h>

#define MAX 100

int q[MAX], front = -1, rear = -1, size;
int dq[MAX], df = -1, dr = -1;

void display() {
    if (front == -1) {
        printf("Queue empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", q[i]);
    printf("\n");
}

void enqueue(int val) {
    if (rear == size - 1) {
        printf("Queue full\n");
        return;
    }
    if (front == -1) front = 0;
    q[++rear] = val;
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
        front++;
    }
    display();
}

void displayDQ() {
    if (df == -1) {
        printf("Deque empty\n");
        return;
    }
    printf("Deque: ");
    int i = df;
    while (1) {
        printf("%d ", dq[i]);
        if (i == dr) break;
        i = (i + 1) % size;
    }
    printf("\n");
}

void insertFront(int val) {
    if ((df == 0 && dr == size - 1) || (dr + 1) % size == df) {
        printf("Deque full\n");
        return;
    }
    if (df == -1) {
        df = dr = 0;
    } else {
        df = (df - 1 + size) % size;
    }
    dq[df] = val;
    printf("%d inserted at front\n", val);
    displayDQ();
}

void insertRear(int val) {
    if ((df == 0 && dr == size - 1) || (dr + 1) % size == df) {
        printf("Deque full\n");
        return;
    }
    if (df == -1) {
        df = dr = 0;
    } else {
        dr = (dr + 1) % size;
    }
    dq[dr] = val;
    printf("%d inserted at rear\n", val);
    displayDQ();
}

void deleteFront() {
    if (df == -1) {
        printf("Deque empty\n");
        return;
    }
    printf("Deleted: %d\n", dq[df]);
    if (df == dr) {
        df = dr = -1;
    } else {
        df = (df + 1) % size;
    }
    displayDQ();
}

void deleteRear() {
    if (df == -1) {
        printf("Deque empty\n");
        return;
    }
    printf("Deleted: %d\n", dq[dr]);
    if (df == dr) {
        df = dr = -1;
    } else {
        dr = (dr - 1 + size) % size;
    }
    displayDQ();
}

int main() {
    int type;
    printf("Select Type:\n1.Queue 2.Deque\nChoice: ");
    scanf("%d", &type);

    printf("Enter size (max 100): ");
    scanf("%d", &size);

    if (type == 1) {
        int choice, val;
        while (1) {
            printf("\n1.Enqueue 2.Dequeue 3.Exit\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Value: ");
                scanf("%d", &val);
                enqueue(val);
            } else if (choice == 2) {
                dequeue();
            } else if (choice == 3) {
                break;
            }
        }
    } else if (type == 2) {
        int choice, val;
        while (1) {
            printf("\n1.Insert Front 2.Insert Rear 3.Delete Front 4.Delete Rear 5.Exit\nChoice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Value: ");
                scanf("%d", &val);
                insertFront(val);
            } else if (choice == 2) {
                printf("Value: ");
                scanf("%d", &val);
                insertRear(val);
            } else if (choice == 3) {
                deleteFront();
            } else if (choice == 4) {
                deleteRear();
            } else if (choice == 5) {
                break;
            }
        }
    }

    return 0;
}
