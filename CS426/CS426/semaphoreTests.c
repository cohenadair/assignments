#include "semaphoreTests.h"

Semaphore* testSemaphoreRef;
Semaphore* testMutexRef;

Code procCode[] = {
	(Word)vHalt,
};

Process* procZeroRef;
Process* procOneRef;
Process* procTwoRef;

void testNewSemaphore() {
	mt_assert(testSemaphoreRef->signalCount == 0);
	mt_assert(testMutexRef->signalCount == 1);
	mt_assert(testSemaphoreRef->waitingRef->isEmpty(testSemaphoreRef->waitingRef));
	mt_assert(testMutexRef->waitingRef->isEmpty(testMutexRef->waitingRef));
}

void testSignalSemaphore() {
	testSemaphoreRef->addProcess(testSemaphoreRef, procTwoRef);
	mt_assert(((Process*)(testSemaphoreRef->waitingRef->head))->state == SUSPENDED);
	
	signalSemaphore(testSemaphoreRef);
	mt_assert(testSemaphoreRef->waitingRef->isEmpty(testSemaphoreRef->waitingRef));
	mt_assert(runnable->tail == (ListNode*)procTwoRef);
	mt_assert(procTwoRef->state == RUNNABLE);
	mt_assert(testSemaphoreRef->signalCount == 0);
	signalSemaphore(testSemaphoreRef);
	mt_assert(testSemaphoreRef->signalCount == 1);
}

void testWaitSemaphore(){
	testSemaphoreRef->addProcess(testSemaphoreRef, procTwoRef);
	mt_assert(testMutexRef->signalCount == 1);
	waitSemaphore(testMutexRef);
	mt_assert(testMutexRef->signalCount == 0);
	waitSemaphore(testMutexRef);
	
	mt_assert(running == procOneRef);
	mt_assert(running->state == RUNNING);

	mt_assert(((Process*)(testMutexRef->waitingRef->tail))->state == SUSPENDED);
	mt_assert(testMutexRef->waitingRef->tail == (ListNode*)procZeroRef);
}

void setupSemaphoreTestCase(){
	testSemaphoreRef = newSemaphore();
	testMutexRef = newMutex();
	procZeroRef = newProcess(&procCode[0].opCode, 16);
	procOneRef = newProcess(&procCode[0].opCode, 16);
	procTwoRef = newProcess(&procCode[0].opCode, 16);
	initializeScheduler(procZeroRef);
	runnable->addLast(runnable, (ListNode*)procOneRef);
}

MT_Test semaphoreTests[]={
	{&testNewSemaphore, "testNewSemaphore"},
	{&testSignalSemaphore, "testSignalSemaphore"},
	{&testWaitSemaphore, "testWaitSemaphore"},
};

MT_TestCase semaphoreTestCase={
	semaphoreTests, &setupSemaphoreTestCase, "semaphoreTests", 3
};
