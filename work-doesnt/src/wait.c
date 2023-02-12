/********** wait.c file **********/
#include "header/wait.h"
// copy the below example if you need access to other global variables from t.c

/********* Required PRE-work ***********/

// 1. Implement ksleep() per the algorithm in 3.4.1
int ksleep(int event)
{
    /* if P1 reject and returns -1 */
    printf("\n\n\n\t\t\t\t\t\t\t\tBEFORE ENQUEUE");
    printStatus(running);
    running->event = event;
    running->status = SLEEP;
    running->pstatus = pstatus[SLEEP];
    enqueue         (&sleepList, running);
    tswitch();
    printf("\n\n\n\t\t\t\t\t\t\t\tAFTER ENQUEUE");
    printStatus(running);
}

// 2. Implement kwakeup per the algorithm in 3.4.2
int kwakeup(int event)
{
    PROCESS *sleeping = sleepList;
    for (; sleeping; ) {
        if (sleeping->event == event) {
            PROCESS *p = dequeue(&sleepList);
            p->status = READY;
            enqueue(&readyQueue, p);
        }
        sleeping = sleeping->next;
    }
}

//==== Test sleep and wakeup commands to verify YOUR ksleep/kwakeup work =====
/******* test sequence ********** 
1. startup
2. P1: sleep: Reject, P1 should never sleep by the sleep command 
       fork; switch ==> fork P2, switch to P2
3. P2: sleep:  enter a value 123 ==> P2 should be SLEEP in sleepList
4. P1: wakeup: enter a value 124: should NOT wakeup P2
       wakeup: enter a value 123: should wakeup P2 ==> P2 in readyQueue
*******************************/


// 3. Modify kfork() to implement processes as a BINARY tree
//    For the running process, print its children list, as in
//    proc 1 running, parent=0, child=[pid, status]->[ ]->...-> NULL


// 4. Implement kexit per the algorithm 3.5.1

int kexit(int exitValue)
{
  // ensure P1 never exit !!!!
  if (running->pid == 1) return -1;

  running->status = FREE;
  running->priority = 0;
  enqueue(&freeList, running);
  printFreeList(freeList);
  tswitch();
}


// 5. Implement kwait() per the algorithm in 3.5.3
int kwait(int *status)
{
    PROCESS *p = running;
    if (!p->child) return -1;
    while (p->child) {
        if (p->child->status == status[ZOMBIE]) {
            *status = p->child->exitCode;
            enqueue(&freeList, p->child);
            return p->child->pid;
        }
    }
    ksleep(running);
}

// 6. Test the wait command to verify YOUR kwait() works
/*************** test sequence *********************
1. startup: P0 switch to P1
2. P1: fork; switch
3. P2: fork; fork; exit ==> P3, P4 are children of P2; P2 exit ==> switch to P1
4. P1: MUST show P2, P3, P4 are children of P1, P2 is a ZOMBIE
       wait: ==> P1 finds a ZOMBIE child P2 and set it FREE
       wait: ==> P1 will SLEEP in kwait() ==> switch to P3
5. P3: wait: no child error
       exit: P3 becomes a ZOMBIE and wakeup P1, but P4 will run
6. P4: exit: P4 becomes a ZOMBIE ==> switch to P1
7. P1: clean up ZOMBIE child p3
       wait: clean up ZOMBIE P4
**************************************************/ 
