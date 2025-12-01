#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size, isFree, pid;
    struct Block *prev, *next;
} Block;

Block *head = NULL;

Block* create(int size) {
    Block *b = malloc(sizeof(Block));
    b->size = size; b->isFree = 1; b->pid = -1;
    b->prev = b->next = NULL;
    return b;
}

void insert(int size) {
    Block *b = create(size);
    if (!head) { head = b; return; }
    Block *p = head;
    while (p->next) p = p->next;
    p->next = b; b->prev = p;
}

void display() {
    Block *p = head;
    printf("\nMemory: ");
    while (p) {
        if (p->isFree) printf("[Free:%d] ", p->size);
        else printf("[P%d:%d] ", p->pid, p->size);
        p = p->next;
    }
    printf("\n");
}

void merge() {
    Block *p = head;
    while (p && p->next) {
        if (p->isFree && p->next->isFree) {
            p->size += p->next->size;
            Block *d = p->next;
            p->next = d->next;
            if (d->next) d->next->prev = p;
            free(d);
        } else p = p->next;
    }
}

void allocate(int pid, int req, int method) {
    Block *p = head, *s = NULL;
    int best = 1e9, worst = -1;

    while (p) {
        if (p->isFree && p->size >= req) {
            if (method == 1) { s = p; break; }
            if (method == 2 && p->size < best) { best = p->size; s = p; }
            if (method == 3 && p->size > worst) { worst = p->size; s = p; }
        }
        p = p->next;
    }
    if (!s) { printf("Allocation failed\n"); display(); return; }

    if (s->size > req) {
        Block *b = create(s->size - req);
        b->next = s->next; b->prev = s;
        if (s->next) s->next->prev = b;
        s->next = b;
        s->size = req;
    }
    s->isFree = 0; s->pid = pid;
    printf("Allocated P%d\n", pid);
    display();
}

void freeProcess(int pid) {
    Block *p = head;
    while (p) {
        if (p->pid == pid) {
            p->isFree = 1; p->pid = -1;
            printf("Freed P%d\n", pid);
            merge();
            display();
            return;
        }
        p = p->next;
    }
    printf("PID not found\n");
    display();
}

int main() {
    int n, size, pid = 1, ch, m, id;

    printf("Blocks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &size);
        insert(size);
    }
    display();

    while (1) {
        printf("\n1.Allocate 2.Free 3.Exit: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Process size: ");
            scanf("%d", &size);
            printf("Method 1.FF 2.BF 3.WF: ");
            scanf("%d", &m);
            allocate(pid++, size, m);
        } else if (ch == 2) {
            printf("PID: ");
            scanf("%d", &id);
            freeProcess(id);
        } else break;
    }
}
