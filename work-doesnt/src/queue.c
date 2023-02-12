#include "header/queue.h"


int enqueue(PROCESS **queue, PROCESS *p)  // NOTE **queue
{
    // enter p into queue by priority; FIFO if same priority
    PROCESS *node = *queue;
    /*printStatus(p);*/
    /* if queue is empty or p.prio > node.prio */
    if (node == 0 || p->priority > node->priority) {
        *queue  = p;
        p->next = node;
    }
    else {
        /* loop until the end of the queue && p.prio > node.prio */
        while (node->next && p->priority <= node->next->priority) {
            node = node->next;
        }
        p->next = node->next;
        node->next = p;
    }
    /* placeholder return */
    return 0;
}

// remove and return first PROCESS from queue
PROCESS *dequeue(PROCESS **queue)  // NOTE **queue
{
    // remove and return FIRST element in queue
    PROCESS *p = *queue;
    if (p) {
        *queue = (*queue)->next;
    }
    return p;
}

void printFreeList(PROCESS *p)  // print list p
{
    PROCESS *q = p;
    // print the list as  freeList=[pid pri]->[pid pri] ->..-> NULL
    printf("\n    FREE  LIST      :");
    for (; q;) {
        printf("[%d %d]->", q->pid, q->priority);
        q = q->next;
    }
    printf("NULL");
    printf("\n       [pid prior.]");
}

void printSleepList(PROCESS *p)  // print list p
{
    // print the list as  sleepList=[pid event]->[pid event] ->..-> NULL
    printf("\n    SLEEP LIST      :");
    for (; p; ++p) {
        printf("[%d %d]->", p->pid, p->event);
    }
    printf("NULL");
    printf("\n       [pid  event]");
}

void printChildList(PROCESS *p)  // print list p
{
    // print the list as  childList=[pid status]->[pid status] ->..-> NULL
    printf("\n    CHILD LIST      :");
    for (; p;) {
        printf("[%d %d]->", p->pid, p->status);
        p = p->child;
    }
    printf("NULL");
    printf("\n       [pid status]");
}

void printList(char *name, PROCESS *p) {
    printf("\n%s%3c=", name, ' ');
    while (p) {
        printf("[%d %d]->", p->pid, p->priority);
        p = p->next;
    }
    printf("NULL");
}

void printReadyQueue(PROCESS *p)  // print list p
{
    PROCESS *q = p;
    // print the list as readyQueue=[pid pri]->..-> NULL
    printf("\n    READY QUEUE     :");
    for (; q;) {
        printf("[%d %d]->", q->pid, q->priority);
        q = q->next;
    }
    printf("NULL");
    printf("\n       [pid prior.]");
}

void printStatus(PROCESS *p) {
    printf("\n    ???_____________________________________________RUNNING STATUS P%d\n", p->pid);
    printf("    ... p->next     =%p\n", p->next);
    printf("    ... p->saved_sp =%p\n", p->saved_sp);
    printf("    ... p->pid      =%d\n", p->pid);
    printf("    ... p->ppid     =%d\n", p->ppid);
    printf("    ... p->status   =%d\t%s\n", p->status, p->pstatus);
    printf("    ... p->priority =%d\n", p->priority);
    printf("    ... p->event    =%d\n", p->event);
    printf("    ... p->exitCode =%d\n", p->exitCode);
    printf("    ???______________________________________________________________\n");
}

