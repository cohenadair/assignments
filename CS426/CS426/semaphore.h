#ifndef _semaphore_
#define _semaphore_

#include "scheduler.h"

typedef void (*pFunVoidProcess)(struct Semaphore*, Process*);

typedef struct Semaphore {
  Word signalCount;
  LinkedList* waitingRef;
  pFunVoidProcess addProcess;
} Semaphore;

Semaphore* newSemaphore(void);
Semaphore* newMutex(void);

void signalSemaphore(Semaphore*);
void waitSemaphore(Semaphore*);

#endif
