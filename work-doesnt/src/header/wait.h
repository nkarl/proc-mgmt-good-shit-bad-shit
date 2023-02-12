#ifndef WAIT_H
#define WAIT_H

#include "type.h"

extern PROCESS *running;
extern PROCESS *freeList;
extern PROCESS *sleepList;
extern PROCESS *readyQueue;
extern char* pstatus[];

int ksleep(int event);
int kwakeup(int event);
int kexit(int exitValue);
int kwait(int *status);

#endif
