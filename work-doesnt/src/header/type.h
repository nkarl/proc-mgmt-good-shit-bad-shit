#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    NPROC  =    9,
    SSIZE  = 1024,  // stack size

    FREE   =    0,  // proc status
    READY  =    1,
    SLEEP  =    2,
    BLOCK  =    3,
    ZOMBIE =    4,
} PROCESS_CONSTANTS;

typedef enum {
    YIELD = 123
} EVENTS;

typedef struct proc{
    struct proc *next;           // next proc pointer
    int         *saved_sp;       // at offset 4: do NOT alter

    int          pid;            // pid = 0 to NPROC-1
    int          ppid;           // parent pid
    int          status;         // PROC status: FREE|READY|etc
    char        *pstatus;        // PROC status: FREE|READY|etc
    int          priority;       // scheduling priority

    int          event;          // event to sleep on
    int          exitCode;       // exit code value

    struct proc *child;          // first child PROC pointer
    struct proc *sibling;        // sibling PROC pointer
    struct proc *parent;         // parent PROC pointer

    size_t       kstack[SSIZE];  // processs stack, each process has its own stack
} PROCESS;

#endif
