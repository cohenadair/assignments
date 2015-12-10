#include "cpuTests.h"
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

Code codeHalt[] = {
};

Code codeThreePlusFour[] = {
  (Word)moveLitR1,
  3,
  (Word)moveLitR2,
  4,
  (Word)saddR1R2R0,
  (Word)vHalt
};

Code codeFourMinusThree[] = {
  (Word)moveLitR1,
  4,
  (Word)moveLitR2,
  3,
  (Word)ssubR1R2R0,
  (Word)vHalt
};

Code codeFourMinusFour[] = {
  (Word)moveLitR1,
  4,
  (Word)moveLitR2,
  4,
  (Word)ssubR1R2R0,
  (Word)vHalt
};

Code codeVarMinusMinusR3R1R3[] = {
  (Word)moveLitR1,
  1,
  (Word)moveLitR3,
  4,
  (Word)ssubR3R1R3,
  (Word)vHalt
};

Code codeVarMinusMinusR4R1R4[] = {
  (Word)moveLitR1,
  1,
  (Word)moveLitR4,
  4,
  (Word)ssubR4R1R4,
  (Word)vHalt
};

Code codeVarPlusPlusR1R3R3[] = {
  (Word)moveLitR1,
  1,
  (Word)moveLitR3,
  4,
  (Word)saddR1R3R3,
  (Word)vHalt
};

Code codeVarPlusPlusR1R4R4[] = {
  (Word)moveLitR1,
  1,
  (Word)moveLitR4,
  4,
  (Word)saddR1R4R4,
  (Word)vHalt
};

Code codeFourTimesThree[] = {
  (Word)moveLitR1,
  4,
  (Word)moveLitR2,
  3,
  (Word)smulR1R2R0,
  (Word)vHalt
};

Code codeBranchTwo[] = {
  (Word)branch,
  2,
  (Word)moveLitR1,
  4,
  (Word)vHalt
};

/*
loop start: count + 0
            branch z loop end
            moveLitR1,
            1,
            ssubR1R3R3,
            saddR1R4R4,
            branch loop start
            loop end:
*/
Code codeNineForLoop[] = {
  (Word)moveLitR3,
  9,
  (Word)moveLitR1,
  0,
  (Word)saddR1R3R3,
  (Word)branchZ,
  6,
  (Word)moveLitR1,
  1,
  (Word)ssubR3R1R3,
  (Word)saddR1R4R4,
  (Word)branch,
  -11,
  (Word)vHalt
};

// r0 factorial( n ){
//	if( n == 0 )
//		goto baseCase;
//	r0 = n - 1;
//  r1 = n;
//	return r0 * r1;
// baseCase:
//	return 1;
// }

Code codeForFactorial[] = {
	(Word)pushFP,		// r0 factorial( n )
	(Word)moveSPFP,		// {
	(Word)moveIndexFPR1,//		r1 = n;
	2,					//
	(Word)saddR1R1R0,	//		if( r1 == 0 )
	(Word)branchZ,		//			goto baseCase;
	12,					//
	(Word)moveLitR2,	//		r0 = r1 - 1;
	1,					//
	(Word)ssubR1R2R0,	//
	(Word)pushR0,		//		call(factorial(r0);
	(Word)call,			//
	(Word)codeForFactorial,	//
	(Word)drop,			//
	(Word)moveIndexFPR1,//		r1 = n;
	2,					//
	(Word)smulR0R1R0,	//		return r1 * r0;
	(Word)popFP,		//
	(Word)ret,			//baseCase:
	(Word)moveLitR0,	//		return 1;
	1,					//
	(Word)popFP,		//
	(Word)ret			// }
};

Code codeForFunctionCall[] = {
	(Word)moveLitR0,
	6,
	(Word)pushR0,
	(Word)call,
	(Word)codeForFactorial,
	(Word)drop,
	(Word)vHalt
};

Code codeLoopFactorial[] = {
	(Word)moveLitR3,
	100000,
	(Word)moveLitR1,
	0,
	(Word)saddR1R3R3,
	(Word)branchZ,
	12,
	(Word)moveLitR1,
	1,
	(Word)ssubR3R1R3,
	(Word)saddR1R4R4,
	(Word)moveLitR0,
	6,
	(Word)pushR0,
	(Word)call,
	(Word)codeForFactorial,
	(Word)drop,
	(Word)branch,
	-17,
	(Word)vHalt
};

void testAdditionThreePlusFour() {
  regs.pc.opCodeRef = &codeThreePlusFour[0].opCode;
  interp();
  mt_assert(regs.r0.integer == 7);
  mt_assert(regs.z == 0);
}

void testVarPlusPlusR1R3R3(){
  regs.pc.opCodeRef = &codeVarPlusPlusR1R3R3[0].opCode;
  interp();
  mt_assert(regs.r3.integer == 5);
}

void testVarPlusPlusR1R4R4(){
  regs.pc.opCodeRef = &codeVarPlusPlusR1R4R4[0].opCode;
  interp();
  mt_assert(regs.r4.integer == 5);
}

void testSubtractionFourMinusThree() {
  regs.pc.opCodeRef = &codeFourMinusThree[0].opCode;
  interp();
  mt_assert(regs.r0.integer == 1);
  mt_assert(regs.z == 0);
}

void testSubtractionFourMinusFour() {
  regs.pc.opCodeRef = &codeFourMinusFour[0].opCode;
  interp();
  mt_assert(regs.r0.integer == 0);
  mt_assert(regs.z == 1);
}

void testVarMinusMinusR3R1R3(){
  regs.pc.opCodeRef = &codeVarMinusMinusR3R1R3[0].opCode;
  interp();
  mt_assert(regs.r3.integer == 3);
}

void testVarMinusMinusR4R1R4(){
  regs.pc.opCodeRef = &codeVarMinusMinusR4R1R4[0].opCode;
  interp();
  mt_assert(regs.r4.integer == 3);
}

void testMulFourTimesThree() {
  regs.pc.opCodeRef = &codeFourTimesThree[0].opCode;
  interp();
  mt_assert(regs.r0.integer == 12);
}

void testBranchTwo(){
  regs.pc.opCodeRef = &codeBranchTwo[0].opCode;
  interp();
  mt_assert(regs.r1.integer == 0);
}

void testNineForLoop(){
  regs.pc.opCodeRef = &codeNineForLoop[0].opCode;
  interp();
  //well if it makes it passed interp, it means the branch worked, otherwise it'll error out
  mt_assert(1);
}

void testInterruptDispatch(){
  regs.pc.opCodeRef = &codeThreePlusFour[0].opCode;
  intReg = intReg|TST_INT;
  interp();
  mt_assert(regs.r3.word == 42);
  mt_assert(intReg == 0);
}

void testFunctionCallAndReturn(){
	regs.pc.opCodeRef = &codeForFunctionCall[0].opCode;
	interp();
	mt_assert(regs.r0.word == 720);
}

void testTimerInterrupt(){
	int result;
	struct timeval start;
	struct timeval stop;
	regs.pc.opCodeRef = &codeLoopFactorial[0].opCode;
	interp();
	mt_assert(runClock > 10);
}

static Process *runningProcessRef;

void setupCpuTestCase() {
	resetCpu();
	runningProcessRef = newProcess(&codeHalt[0].opCode, DEFAULT_PROCESS_SIZE);
	initializeScheduler(runningProcessRef);
	regs = runningProcessRef->regs;
}

MT_Test cpuTestTests[] = {
	{ &testAdditionThreePlusFour, "testAdditionThreePlusFour" },
	{ &testVarPlusPlusR1R3R3, "testVarPlusPlusR1R3R3" },
	{ &testVarPlusPlusR1R4R4, "testVarPlusPlusR1R4R4" },
	{ &testSubtractionFourMinusThree, "testSubtractionFourMinusThree" },
	{ &testSubtractionFourMinusFour, "testSubtractionFourMinusFour" },
	{ &testVarMinusMinusR3R1R3, "testVarMinusMinusR3R1R3" },
	{ &testVarMinusMinusR4R1R4, "testVarMinusMinusR4R1R4" },
	{ &testMulFourTimesThree, "testMulFourTimesThree" },
	{ &testBranchTwo, "testBranchTwo" },
	{ &testNineForLoop, "testNineForLoop" },
	{ &testInterruptDispatch, "testInterruptDispatch"},
	{ &testFunctionCallAndReturn, "testFunctionCallAndReturn"},
	{ &testTimerInterrupt, "testTimerInterrupt" },
};

MT_TestCase cpuTestTestsCase =
	{ cpuTestTests, &setupCpuTestCase, "CPU Test Tests", 13 };
