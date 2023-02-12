int enqueue(PROC **queue, PROC *p);  // NOTE **queue
PROC *dequeue(PROC **queue);         // NOTE **queue 
int printFreeList(PROC *p);  // print list p
int printSleepList(PROC *p);  // print list p
int printChildList(PROC *p);  // print list p
int printReadyQueue(PROC *p); // print list p

int enqueue(PROC **queue, PROC *p)  // NOTE **queue
{
  // enter p into queue by priority; FIFO if same priority
  PROC *q = *queue;
  if (q == 0 || p->priority > q->priority) {
      *queue  = p;
      p->next = q;
  }
  else {
      while (q->next && p->priority <= q->next->priority)
          q = q->next;
      p->next = q->next;
      q->next = p;
  }
}

// remove and return first PROC from queue 
PROC *dequeue(PROC **queue)         // NOTE **queue 
{
  // remove and return FIRST element in queue
  PROC *p = *queue;
  if (p)
      *queue = (*queue)->next;
  return p;
}

int printFreeList(PROC *p)  // print list p
{
   // print the list as  freeList=[pid pri]->[pid pri] ->..-> NULL
   printf("\n FREE LIST\t:");
   for (; p;) {
       printf("[%d %d] -> ", p->pid, p->priority);
       p = p->next;
   }
   printf("NULL");
   printf("\n");
}

int printSleepList(PROC *p)  // print list p
{
   // print the list as  sleepList=[pid event]->[pid event] ->..-> NULL 
   printf("\n SLEEP LIST\t:");
   for (; p;) {
       printf("[%d %d] -> ", p->pid, p->event);
       p = p->next;
   }
   printf("NULL");
   printf("\n");
}

int printChildList(PROC *p)  // print list p
{
   // print the list as  childList=[pid status]->[pid status] ->..-> NULL 
   printf("\n CHILD LIST\t:");
   for (; p;) {
       printf("[%d %d] -> ", p->pid, p->status);
       p = p->next;
   }
   printf("NULL");
   printf("\n");
}

int printReadyQueue(PROC *p) // print list p
{
    // print the list as readyQueue=[pid pri]->..-> NULL
   printf("\n READY QUEUE\t:");
   for (; p;) {
       printf("[%d %d] -> ", p->pid, p->priority);
       p = p->next;
   }
   printf("NULL");
   printf("\n");
}

