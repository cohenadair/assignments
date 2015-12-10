// Code developed for CS426 by the mob 2015.

#include "process.h"
#include <stdlib.h>
#include <stdio.h>

// nextPid()
// This function has a grievous bug.
// After a Words worth of processes have been spawned,
// It will just loop back...
// FIX ME!!!

Word nextPid(){
	static Word currentPid = -1;
	return ++currentPid;
}

Process *newProcess(OpCode* entry, Word size){
	Process *processRef = (Process *)calloc(1, sizeof(Process));
	if(processRef == NULL){
		return (Process*)NULL;
	}
	processRef->memMap.baseOfMemory = calloc(1, size);
	if( processRef->memMap.baseOfMemory == NULL ){
		free(processRef);
		return (Process*)NULL;
	}
	processRef->memMap.sizeOfMemory = size;
	processRef->regs.sp.ref =
		(Word*)processRef->memMap.baseOfMemory + size/sizeof(Word);
	processRef->regs.pc.opCodeRef = entry;
	processRef->state = NEW;
	processRef->pid = nextPid();
	return processRef;
}

void freeProcess(Process* processRef){
	
}
