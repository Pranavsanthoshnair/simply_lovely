#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size;
    int isFree;
    int pid;
    struct Block *next;
};

struct Block *head = NULL;

struct Block* createBlock(int size) {
    struct Block *b = (struct Block*)malloc(sizeof(struct Block));
    b->size = size;
    b->isFree = 1;
    b->pid = -1;
    b->next = NULL;
    return b;
}

void insertBlock(int size) {
    struct Block *b = createBlock(size);
    if (head == NULL) {
        head = b;
        return;
    }
    struct Block *temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = b;
}

void display() {
    struct Block *temp = head;
    printf("\nMemory: ");
    while (temp != NULL) {
        if (temp->isFree)
            printf("[Free:%d] ", temp->size);
        else
            printf("[P%d:%d] ", temp->pid, temp->size);
        temp = temp->next;
    }
    printf("\n");
}

void mergeBlocks() {
    struct Block *temp = head;
    while (temp != NULL && temp->next != NULL) {
        if (temp->isFree && temp->next->isFree) {
            temp->size += temp->next->size;
            struct Block *del = temp->next;
            temp->next = del->next;
            free(del);
        } else {
            temp = temp->next;
        }
    }
}

void allocate(int pid, int size, int method) {
    struct Block *temp = head, *selected = NULL;
    
    if (method == 1) {
        while (temp != NULL) {
            if (temp->isFree && temp->size >= size) {
                selected = temp;
                break;
            }
            temp = temp->next;
        }
    } else if (method == 2) {
        int best = 1e9;
        while (temp != NULL) {
            if (temp->isFree && temp->size >= size && temp->size < best) {
                best = temp->size;
                selected = temp;
            }
            temp = temp->next;
        }
    } else {
        int worst = -1;
        while (temp != NULL) {
            if (temp->isFree && temp->size >= size && temp->size > worst) {
                worst = temp->size;
                selected = temp;
            }
            temp = temp->next;
        }
    }
    
    if (selected == NULL) {
        printf("Cannot allocate P%d (size %d)\n", pid, size);
        display();
        return;
    }
    
    if (selected->size > size) {
        struct Block *newBlock = createBlock(selected->size - size);
        newBlock->next = selected->next;
        selected->next = newBlock;
        selected->size = size;
    }
    
    selected->isFree = 0;
    selected->pid = pid;
    printf("P%d allocated (%d units)\n", pid, size);
    display();
}

void freeProcess(int pid) {
    struct Block *temp = head;
    while (temp != NULL) {
        if (temp->pid == pid) {
            temp->isFree = 1;
            temp->pid = -1;
            printf("P%d freed\n", pid);
            mergeBlocks();
            display();
            return;
        }
        temp = temp->next;
    }
    printf("P%d not found\n", pid);
}

int main() {
    int n, choice, size, pid = 1;
    printf("Number of blocks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &size);
        insertBlock(size);
    }
    
    while (1) {
        printf("\n1.Allocate 2.Free 3.Exit\nChoice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("Process size: ");
            scanf("%d", &size);
            printf("Method (1.First 2.Best 3.Worst): ");
            scanf("%d", &choice);
            allocate(pid++, size, choice);
        } else if (choice == 2) {
            printf("Process ID: ");
            scanf("%d", &size);
            freeProcess(size);
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}
