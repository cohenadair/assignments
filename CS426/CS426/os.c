#include "scheduler.h"

Process* process0Ref;
char message[] = "hello world!\n";
char messageA[] = "A";
char messageB[] = "B";

//get rid of magic numbers
Code procBCode[] = {
  (Word)moveLitR0,
  3,//SYS_WRITE
  (Word)moveLitR1,
  1,//stdout
  (Word)moveLitR2,
  (Word)messageB,
  (Word)moveLitR3,
  1,
  (Word)swi,
  (Word)branch,
  -11,
};
Code bootCode[] = {
  (Word)moveLitR0,
  4,//SYS_NEWPROCESS
  (Word)moveLitR1,
  (Word)procBCode,
  (Word)moveLitR2,
  DEFAULT_PROCESS_SIZE,
  (Word)swi,
  (Word)moveLitR0,
  3,//SYS_WRITE
  (Word)moveLitR1,
  1,//stdout
  (Word)moveLitR2,
  (Word)messageA,
  (Word)moveLitR3,
  1,
  (Word)swi,
  (Word)branch,
  -11,
  (Word)moveLitR0,
  5,//SYS_EXIT
  (Word)swi,
};

int main(int argc, char* argv[]){
  process0Ref = newProcess(&bootCode[0].opCode,DEFAULT_PROCESS_SIZE);
	initializeScheduler(process0Ref);
  interp();
  return 0;
}
