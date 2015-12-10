#ifndef _process_
#define _process_
#define DEFAULT_PROCESS_SIZE (16 * 1024)
#include "mem.h"

typedef enum {
	NEW,
	RUNNABLE,
	RUNNING,
	SUSPENDED,
	TERMINATED,
} ProcessState;

typedef struct Process {
	struct Process *next;
	RegisterFile 	regs;
	MemoryMap 		memMap;
	Word			pid;
	ProcessState	state;
}Process;

Process*newProcess(OpCode* entry, Word size);
void freeProcess(Process* processRef);



#endif
