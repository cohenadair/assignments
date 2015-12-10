#include "semaphore.h"
#include "linkedList.h"

void semaphoreAddProcess(Semaphore *semaphoreRef, Process *processRef);

Semaphore* semaphoreConstructor(Word signalCount) {
	Semaphore *semaphoreRef = (Semaphore *)calloc(1, sizeof(Semaphore));

	if (semaphoreRef == NULL)
		return NULL;

	semaphoreRef->signalCount = signalCount;
	semaphoreRef->waitingRef = newLinkedList();
	semaphoreRef->addProcess = semaphoreAddProcess;

	return semaphoreRef;
}

Semaphore* newSemaphore(void) {
	return semaphoreConstructor(0);
}

Semaphore* newMutex(void) {
	return semaphoreConstructor(1);
}

void signalSemaphore(Semaphore* semaphoreRef) {
	if (semaphoreRef->waitingRef->isEmpty(semaphoreRef->waitingRef)) {
		semaphoreRef->signalCount++;
		return;
	}

	Process *nextProcess = (Process *)semaphoreRef->waitingRef->removeFirst(semaphoreRef->waitingRef);
	nextProcess->state = RUNNABLE;
	runnable->addLast(runnable, (ListNode *)nextProcess);
}

void waitSemaphore(Semaphore* semaphoreRef) {
	if (semaphoreRef->signalCount > 0) {
		semaphoreRef->signalCount--;
		return;
	}

	semaphoreRef->addProcess(semaphoreRef, running);
	scheduleProcess();
}

void semaphoreAddProcess(Semaphore *semaphoreRef, Process *processRef) {
	processRef->state = SUSPENDED;
	semaphoreRef->waitingRef->addLast(semaphoreRef->waitingRef, (ListNode *)processRef);
}
