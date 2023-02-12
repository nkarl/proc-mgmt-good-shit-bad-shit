#ifndef QUEUE_H
#define QUEUE_H

#include "wait.h"

void     printStatus     ( PROCESS *p);

int      enqueue         ( PROCESS **queue, PROCESS *p);
PROCESS *dequeue         ( PROCESS **queue);

void     printFreeList   ( PROCESS *p);
void     printSleepList  ( PROCESS *p);
void     printChildList  ( PROCESS *p);
void     printList       ( char *name, PROCESS *p);

void     printReadyQueue ( PROCESS *p);

#endif

