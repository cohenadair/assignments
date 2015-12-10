#include "scheduler.h"

LinkedList* runnable;
Process* running;

void initializeScheduler(Process* processRef) {
  running = processRef;
  running->state = RUNNING;
  regs = running->regs;
  runnable = newLinkedList();
  if (runnable == NULL){
    exit(-1);
  }
}

//Try to schedule next best process
void switchProcess(){
  if (runnable->isEmpty(runnable))
    return;
  descheduleProcess();
  scheduleProcess();
}

void descheduleProcess(){
  running->regs = regs;
  running->state = RUNNABLE;
  runnable->addLast(runnable, (ListNode *)running);
}

void scheduleProcess(){
  running = (Process *)runnable->removeFirst(runnable);
  if(running == NULL){
    vHalt();
    return;
  }
  running->state = RUNNING;
  regs = running->regs;
}
