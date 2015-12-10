#ifndef _scheduler_
#define _scheduler_
#include "process.h"
#include "linkedList.h"

extern LinkedList* runnable;
extern Process* running;

void initializeScheduler(Process* processRef);
void switchProcess();
void descheduleProcess();
void scheduleProcess();

#endif
