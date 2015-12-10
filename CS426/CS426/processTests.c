#include "processTests.h"

Code someCode[] = {
	(Word)moveLitR1,
	3,
	(Word)moveLitR2,
	4,
	(Word)saddR1R2R0,
	(Word)vHalt
};

void testNewProcess(){
	Process * process=newProcess(&someCode[0].opCode, DEFAULT_PROCESS_SIZE-1);
	mt_assert(process);
	mt_assert(!process->next);
	mt_assert(process->regs.pc.opCodeRef == &someCode[0].opCode);
	mt_assert(process->regs.sp.ref == 
	(Word*)process->memMap.baseOfMemory + (DEFAULT_PROCESS_SIZE-1)/sizeof(Word));
	mt_assert((process->regs.sp.word % sizeof(Word)) == 0);
	mt_assert(process->memMap.baseOfMemory);
	mt_assert(process->memMap.sizeOfMemory == DEFAULT_PROCESS_SIZE-1);
	mt_assert(process->state == NEW);
	mt_assert(process->pid + 1 == newProcess(&someCode[0].opCode, 16)->pid);
}

void setupProcessTestCase(){}

MT_Test processTests[]={
	{&testNewProcess,"testNewProcess"},

};

MT_TestCase processTestCase={
	processTests, &setupProcessTestCase,"processTests",1
};
