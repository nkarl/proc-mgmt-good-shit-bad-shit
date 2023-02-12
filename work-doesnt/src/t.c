/***************************************************************
 ***************** A Multitasking System ***********************
 ***************************************************************/
#include "header/queue.h"

/* INIT global processes and process queues */
PROCESS  process[NPROC] ; // 9 PROCs
PROCESS *freeList       ; // FREE proc list
PROCESS *readyQueue     ; // priority queue of READY procs
PROCESS *sleepList      ; // list of SLEEP procs
PROCESS *running        ; // pointer to current RUNNING proc

const int APP_RUNNING = READY;
char *pstatus[] = {"FREE", "READY", "SLEEP", "BLOCK", "ZOMBIE", "RUNNING"};

int process_body (            );
int kfork        ( int *, int );
int scheduler    (            );
int ps           (            );
int init         (            );

void do_switch() {
    tswitch();
}

/* forking a process */
int kfork(int (*func), int priority) {
    /*** get a proc from freeList for child proc: ***/
    PROCESS *p = dequeue(&freeList);
    if (!p) {
        printf("> no more proc\n"); return -1;
    }

    /* initialize the new proc and its stack */
    p->next     = 0;
    p->status   = READY          ;
    p->pstatus  = pstatus[READY] ;
    p->priority = priority       ; // for ALL PROCs except P0
    p->ppid     = running->pid   ;
    p->parent   = running        ;
    p->child    = p->sibling = 0 ;

    //                    -1   -2  -3  -4  -5  -6  -7  -8   -9
    // kstack contains: |retPC|eax|ebx|ecx|edx|ebp|esi|edi|eflag|
    for (int i=1; i<=NPROC; ++i) {
        p->kstack[SSIZE - i] = 0;
    }

    p->kstack[SSIZE - 1] = func;
    p->saved_sp          = &(p->kstack[SSIZE - 9]);

    enqueue(&readyQueue, p);
    return p->pid;
}

/*void do_kfork(void *func, int priority) {*/
    /*int child = kfork(func, priority);*/
    /*if (child < 0) {*/
        /*printf("\n> kfork FAILED.\n");*/
    /*} else {*/
        /*printf("P%d kforked a child = %d\n", running->pid, child);*/
        /*printReadyQueue(readyQueue);*/
    /*}*/
/*}*/

/*************** scheduler ***************************/
int scheduler() {
    printf("\n> P%d: in\tscheduler()", running->pid);
    if (running->status == READY)
        enqueue(&readyQueue, running);
    printf("\n..............................");
    printReadyQueue(readyQueue);
    printf("\n..............................");

    running = dequeue(&readyQueue);
    printf("\n> next running = P%d", running->pid);
    printf("\n\n");
    return 0;
}


/* print process status */
int ps() {
    PROCESS *p;
    printf("pid   ppid    status\n");
    printf("--------------------\n");
    for (int i=0; i<NPROC; ++i) {
        p = &process[i];
        printf(" %d      %d     ", p->pid, p->ppid);
        if (p == running)
            printf("%s\n", pstatus[5]);
        else
            printf("%s\n", pstatus[p->status]);
    }
    printStatus(running);
    return 0;
}

/* process process_body function */
int process_body() {
    char command[64];
    while (APP_RUNNING) {
        printf("\n**************************");
        printf("\n> P%d: running, Parent=P%d", running->pid, running->ppid);
        printf("\n..........................");
        printChildList  ( running    );
        printFreeList   ( freeList   );
        printSleepList  ( sleepList  );
        printReadyQueue ( readyQueue );
        printf("\n..........................\n");

        printf("\n\n\n\n> > > input a command\n");
        printf("      COMMAND: [ps|fork|switch] | [sleep|wakeup|exit|wait] : ");
        fgets(command, 64, stdin);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        command[strlen(command) - 1] = 0;  // kill \n at end

        if      (!strcmp (command, "ps"     )) ps      ( );
        else if (!strcmp (command, "fork"   )) kfork   ( process_body, 1 );
        else if (!strcmp (command, "switch" )) tswitch ( );
        else if (!strcmp (command, "sleep"  )) ksleep  ( YIELD  );
        else if (!strcmp (command, "wakeup" )) kwakeup ( SLEEP  );
        else if (!strcmp (command, "exit"   )) kexit   ( ZOMBIE );
        else if (!strcmp (command, "wait"   )) kwait   ( BLOCK  );
        else
            printf("\n> invalid command");
    }
}

/***************************************************************
 * init freeList, readyQ, sleepList
 ***************************************************************/
int init() {
    int i;

    // 1. INIT all PROCs in freeList
    for (i = 0; i < NPROC; ++i) {
        process[i].pid      = i;  // pid = 0 to NPROC-1
        process[i].status   = FREE;
        process[i].priority = 0;
        process[i].next     = (PROCESS *)&process[i + 1];
    }
    process[NPROC - 1].next = 0;

    freeList   = &process[0] ;
    sleepList  = 0           ;
    readyQueue = 0           ;

    // 2. create P0 as the initial running process
    running           = dequeue(&freeList) ;
    running->status   = READY              ;
    running->pstatus  = pstatus[READY]     ;
    running->priority = 0                  ; // P0 has lowest prioriy 0
    running->child    = 0                  ;
    running->sibling  = 0                  ;
    running->parent   = running            ;

    printf("\n> INIT COMPLETE: P0 running");
    printf("\n..............................");
    printFreeList(freeList);
    printf("\n..............................\n");
    return 0;
}

/***************************************************************
 * MAIN APP ENTRY
 ***************************************************************/
int main() {
    printf("\n\n----------------------------------------------------------------------------------------\n");
    printf("Welcome to 360 Multitasking System\n");
    printf("----------------------------------------------------------------------------------------\n");
    init();
    printf("\n\n> P0: fork\tP1");
    kfork(process_body, READY);

    while (APP_RUNNING) {
        if (readyQueue) {
            printf("\n> P0: switch\ttask");
            tswitch();
        }
    }
}
