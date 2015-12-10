#include <stdio.h>
#include "mt_unitTest.h"
#include "mtUnitTestTests.h"
#include "baseTypeTests.h"
#include "cpuTests.h"
#include "processTests.h"
#include "linkedListTests.h"
#include "schedulerTests.h"
#include "semaphoreTests.h"


MT_TestCase *testCases[] = {
	&unitTestTestCase,
	&baseTypeTestCase,
	&cpuTestTestsCase,
	&processTestCase,
	&linkedListTestCase,
	&schedulerTestCase,
	&semaphoreTestCase,
	(MT_TestCase*)0
};

MT_TestRunner runner = { testCases };

int main(int argc, char *argv[]){
	return mt_unitTest_start( argc, argv, runner );
}
