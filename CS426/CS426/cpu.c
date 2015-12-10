#include "cpu.h"
#include "syscall.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

RegisterFile regs;
InterruptRegister intReg;
Word runClock;

void handleClockInterrupt(void);
void handleDiskInterrupt(void);
void handleSoftwareInterrupt(void);
void handleTestInterrupt(void);

OpCode intrVector[MAX_INT] = {
  handleClockInterrupt,
  handleDiskInterrupt,
  handleSoftwareInterrupt,
  handleTestInterrupt,
};

static int isRunning = 0;

static void * timeFunction(void *arg) {
	while (1) {
		usleep(QUANTUM_USEC);
		atomicOr(&intReg, CLK_INT);
	}
	return arg;
}

void handleInterrupts( InterruptRegister ints)
{
  InterruptRegister intr_mask = 1;
  for ( int int_it = 0; int_it < MAX_INT; ++ int_it, intr_mask <<= 1 ) {
    if ( intr_mask & ints ) {
      intrVector[int_it]();
    }
  }
}

// If value currently in register equals old value change register to new value and return true.
#ifdef __linux__
#define atomicCompareAndSwap(valueRef, oldValue, newValue) \
	__sync_bool_compare_and_swap (valueRef, oldValue, newValue)
#endif

#ifdef __APPLE__
#include <libkern/OSAtomic.h>
#define atomicCompareAndSwap(valueRef, oldValue, newValue) \
	OSAtomicCompareAndSwapInt((int)oldValue, (int)newValue, (int *)valueRef)
#endif 


//
void atomicSwap( Word *oldFlagsRef, Word *newFlagsRef)
{
	int done = 0;
	Word oldVal;
	while (!done) {
		oldVal = *oldFlagsRef;
		done = atomicCompareAndSwap(oldFlagsRef, oldVal, *newFlagsRef);
	}
	*newFlagsRef = oldVal;
}

void atomicOr(Word *wordRef, Word mask){
	int done = 0;
	Word oldVal;
	while(!done){
		oldVal = *wordRef;
		done = atomicCompareAndSwap(wordRef, oldVal, oldVal|mask);
	}
}

void resetCpu(void){
	memset((void *)&regs, 0, sizeof(RegisterFile));
	intReg = 0;
	runClock = 0;
}

void interp(void){
	InterruptRegister intRegCopy;

	pthread_t timeThread;
	isRunning = 1;
	if(pthread_create(&timeThread, NULL, timeFunction, NULL)){
		fprintf( stderr, "Could not create time thread.\n" );
		exit(1);
	}
	while(isRunning){
 		while ( 1 ) {
			intRegCopy = 0;
			atomicSwap(&intReg, &intRegCopy);
	  		if (intRegCopy){
  				handleInterrupts(intRegCopy);
  			} else {
        		break;
      		}
    	}
		(*regs.pc.opCodeRef)();
		regs.pc.opCodeRef++;
	}

	pthread_cancel(timeThread);
}

void vHalt(void) {
	isRunning = 0;
}

void moveLitR0(void) {
	regs.pc.opCodeRef++;
	regs.r0.word=*regs.pc.wordRef;
}

void moveLitR1(void) {
	regs.pc.opCodeRef++;
	regs.r1.word=*regs.pc.wordRef;
}

void moveLitR2(void) {
	regs.pc.opCodeRef++;
	regs.r2.word=*regs.pc.wordRef;
}

void moveLitR3(void) {
	regs.pc.opCodeRef++;
	regs.r3.word=*regs.pc.wordRef;
}

void moveLitR4(void) {
	regs.pc.opCodeRef++;
	regs.r4.word=*regs.pc.wordRef;
}

void moveSPFP(void) {
	regs.fp.word = regs.sp.word;
}

void moveIndexFPR1(void) {
	Integer index = *++regs.pc.integerRef;
	regs.r1.word = regs.fp.wordRef[index];
}

void saddR1R1R0(void) {
	regs.r0.integer=regs.r1.integer+regs.r1.integer;
	regs.z = (regs.r0.integer == 0)?1:0;
}

void saddR1R2R0(void) {
	regs.r0.integer=regs.r1.integer+regs.r2.integer;
	regs.z = (regs.r0.integer == 0)?1:0;
}

void saddR1R3R3(void){
	regs.r3.integer=regs.r1.integer+regs.r3.integer;
	regs.z = (regs.r3.integer == 0)?1:0;
}

void saddR1R4R4(void){
	regs.r4.integer=regs.r1.integer+regs.r4.integer;
	regs.z = (regs.r4.integer == 0)?1:0;
}

void ssubR1R2R0(void){
  regs.r0.integer=regs.r1.integer-regs.r2.integer;
  regs.z = (regs.r0.integer == 0)?1:0;
}

void ssubR3R1R3(void){
  regs.r3.integer=regs.r3.integer-regs.r1.integer;
  regs.z = (regs.r3.integer == 0)?1:0;
}

void ssubR4R1R4(void){
  regs.r4.integer=regs.r4.integer-regs.r1.integer;
  regs.z = (regs.r4.integer == 0)?1:0;
}

void smulR0R1R0(void){
  regs.r0.integer=regs.r0.integer*regs.r1.integer;
  regs.z = (regs.r0.integer == 0)?1:0;
}

void smulR1R2R0(void){
  regs.r0.integer=regs.r1.integer*regs.r2.integer;
  regs.z = (regs.r0.integer == 0)?1:0;
}

void branch(void){
	regs.pc.opCodeRef++;
	regs.pc.opCodeRef += *regs.pc.integerRef;
}

void branchZ(void){
	regs.pc.opCodeRef++;
	if (regs.z) {
		regs.pc.opCodeRef += *regs.pc.integerRef;
	}
}

void drop(void){
	regs.sp.wordRef++;
}

void pushFP(void){
	*--regs.sp.wordRef = regs.fp.word;
}

void popFP(void){
	regs.fp.word = *regs.sp.wordRef++;
}
void pushR0(void){
	*--regs.sp.wordRef = regs.r0.word;
}

void popR0(void){
	regs.r0.word = *regs.sp.wordRef++;
}

void call(void){
	Word *func = *++regs.pc.wordRefRef;
	*--regs.sp.wordRef = regs.pc.word;
	regs.pc.wordRef = func - 1;
}

void ret(void){
	regs.pc.word = *regs.sp.wordRef++;
}

void swi(void) {
	atomicOr(&intReg, SWI_INT);
}

void handleClockInterrupt(void) {
  runClock++;
  switchProcess();
}

void handleDiskInterrupt(void) {

}

void handleSoftwareInterrupt(void) {
  sysCallTable[regs.r0.word]();
}

void handleTestInterrupt(void) {
  regs.r3.word = 42;
}
