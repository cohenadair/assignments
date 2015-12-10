#include "syscall.h"

void sys_open(void);
void sys_close(void);
void sys_read(void);
void sys_write(void);
void sys_newProcess(void);
void sys_exit(void);

SysCall sysCallTable[] = {
	sys_open,
	sys_close,
	sys_read,
	sys_write,
	sys_newProcess,
	sys_exit,
};

void sys_open(void) {

}

void sys_close(void) {

}

void sys_read(void) {

}

void sys_write(void) {
	regs.r0.word = write(regs.r1.word,regs.r2.ref,regs.r3.word);
}

void sys_newProcess(void) {
	Process* newProc = newProcess(regs.r1.opCodeRef,regs.r2.word);
	runnable->addLast(runnable,(ListNode*)newProc);
}

//if we need it to wait for parents here is where we
//queue up on the zombie process list
void sys_exit(void) {
	running->state = TERMINATED;
	freeProcess(running);
	scheduleProcess();
}
