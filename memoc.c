#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size, isFree, pid;
    struct Block *next;
};

struct Block *head = NULL;

struct Block* createBlock(int size) {
    struct Block *b = malloc(sizeof(struct Block));
    b->size = size;
    b->isFree = 1;
    b->pid = -1;
    b->next = NULL;
    return b;
}

void insertBlock(int size) {
    struct Block *b = createBlock(size);
    if (!head) {
        head = b;
        return;
    }
    struct Block *temp = head;
    while (temp->next) temp = temp->next;
    temp->next = b;
}

void display() {
    printf("\nMemory: ");
    for (struct Block *t = head; t; t = t->next)
        printf(t->isFree ? "[Free:%d] " : "[P%d:%d] ", t->isFree ? t->size : t->pid, t->size);
    printf("\n");
}

void mergeBlocks() {
    for (struct Block *t = head; t && t->next; ) {
        if (t->isFree && t->next->isFree) {
            t->size += t->next->size;
            struct Block *del = t->next;
            t->next = del->next;
            free(del);
        } else t = t->next;
    }
}

void allocate(int pid, int size, int method) {
    struct Block *temp = head, *selected = NULL;
    int best = (method == 2) ? 1e9 : -1;
    
    while (temp) {
        if (temp->isFree && temp->size >= size) {
            if (method == 1) { selected = temp; break; }
            if ((method == 2 && temp->size < best) || (method == 3 && temp->size > best)) {
                best = temp->size;
                selected = temp;
            }
        }
        temp = temp->next;
    }
    
    if (!selected) {
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
    for (struct Block *t = head; t; t = t->next) {
        if (t->pid == pid) {
            t->isFree = 1;
            t->pid = -1;
            printf("P%d freed\n", pid);
            mergeBlocks();
            display();
            return;
        }
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
        } else if (choice == 3) break;
    }
    return 0;
}
