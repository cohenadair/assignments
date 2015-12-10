#ifndef _cpu_
#define _cpu_

#include <stdlib.h>

#ifdef Linux32
typedef int Integer;
typedef unsigned int Word;
#endif

#ifdef Linux64
typedef long Integer;
typedef unsigned long Word;
#endif

// temporal resolution of our simulation
#define QUANTUM_USEC 10000 // 100th of a second

typedef void * Ref;

typedef void (*OpCode)(void);

typedef union
{
	Word word;
	OpCode opCode;
	Integer integer;
} Code;

typedef union
{
	Integer	integer;
	Integer *integerRef;
	Word	word;
	Word 	*wordRef;
	Word	**wordRefRef;
	Ref		ref;
	OpCode	*opCodeRef;
} Register;

typedef struct
{
	Register	pc;
	Register	sp;
	Register	fp;
	Register	r0;
	Register	r1;
	Register	r2;
	Register 	r3;
	Register	r4;
	Word 		z:1;
	Register	resv1;
} RegisterFile;

// Type for interrupts, currently only one defined.
typedef Word InterruptRegister;
#define CLK_INT	1
#define DSK_INT 2
#define SWI_INT 4
#define TST_INT 8
#define MAX_INT TST_INT

// Atomic operations for setting and clearing interrupts.
void atomicSwap( Word *oldFlagsRef, Word *newFlagsRef);
void atomicOr(Word *wordRef, Word mask);

//Prototype for interpreter function
void resetCpu(void);
void interp(void);

//Types and externs for software interrupts
typedef void (*SysCall)(void);
extern SysCall sysCallTable[];
void switchProcess();

//OpCodes for machine
void vHalt(void); // need to change the name
void moveLitR0(void);
void moveLitR1(void);
void moveLitR2(void);
void moveLitR3(void);
void moveLitR4(void);
void moveSPFP(void);
void moveIndexFPR1(void);
void saddR1R1R0(void);
void saddR1R2R0(void);
void saddR1R3R3(void);
void saddR1R4R4(void);
void smulR0R1R0(void);
void smulR1R2R0(void);
void ssubR1R2R0(void);
void ssubR3R1R3(void);
void ssubR4R1R4(void);
void branch(void);
void branchZ(void);
void drop(void);
void pushFP(void);
void popFP(void);
void pushR0(void);
void popR0(void);
void call(void);
void ret(void);
void swi(void);

extern RegisterFile regs;
extern InterruptRegister intReg;
extern Word runClock;

#endif
