#include "schedulerTests.h"
#include <string.h>

Process* processARef;
Process* processBRef;
Process* processCRef;
Process* processDRef;
 
Code someMoreCode[] = {
	(Word)moveLitR1,
	3,
	(Word)moveLitR2,
	4,
	(Word)saddR1R2R0,
	(Word)vHalt
};

void testInitializeScheduler(){
	mt_assert(running == processARef);
	mt_assert(processARef->state == RUNNING);
	mt_assert(memcmp(&processARef->regs, &regs, sizeof(RegisterFile)) == 0);
	mt_assert(!runnable->isEmpty(runnable));
}

void testDescheduleProcess(){
	descheduleProcess();
	mt_assert(runnable->tail == (ListNode*)processARef);
	mt_assert(runnable->tail->next == NULL);
	mt_assert(((Process*)runnable->tail)->state == RUNNABLE);
	mt_assert(runnable->head == (ListNode*)processBRef);
}

void testScheduleProcess(){
	scheduleProcess();
	mt_assert(running == processBRef);
	mt_assert(running->state == RUNNING);
	mt_assert(running->next == NULL);
	mt_assert(runnable->head == (ListNode*)processCRef);
}
	
void testSwitchProcess(){
	switchProcess();
    mt_assert(running == processBRef);
    mt_assert(running->state == RUNNING);
    mt_assert(running->next == NULL);
    mt_assert(runnable->head == (ListNode*)processCRef);
    mt_assert(runnable->tail == (ListNode*)processARef); 
    mt_assert(runnable->tail->next == NULL);
    mt_assert(((Process*)runnable->tail)->state == RUNNABLE);
}

void setupSchedulerTestCase (){
	resetCpu();
	processARef = newProcess(&someMoreCode[0].opCode,16);
	processBRef = newProcess(&someMoreCode[0].opCode,16);
	processCRef = newProcess(&someMoreCode[0].opCode,16);
	processDRef = newProcess(&someMoreCode[0].opCode,16);
	initializeScheduler(processARef);
	runnable->addLast(runnable,(ListNode*)processBRef);
	runnable->addLast(runnable,(ListNode*)processCRef);
	runnable->addLast(runnable,(ListNode*)processDRef);
}

MT_Test schedulerTests[] = {
	{&testInitializeScheduler,"testInitializeScheduler"},
	{&testDescheduleProcess, "testDescheduleProcess"},
	{&testScheduleProcess, "testScheduleProcess"},
	{&testSwitchProcess, "testSwitchProcess"},
};

MT_TestCase schedulerTestCase = {
  schedulerTests,setupSchedulerTestCase,"schedulerTests",4
};
