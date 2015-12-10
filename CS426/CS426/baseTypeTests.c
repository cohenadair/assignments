#include "baseTypeTests.h"

void testSizeOfPointerAndLong()
{
	mt_assert( sizeof(long) == sizeof(void *) );
}

void setupBaseTypeTestCase() {
	
}

MT_Test baseTypeTests[] = {
	{ &testSizeOfPointerAndLong, "testSizeOfPointerAndLong" },
};

MT_TestCase baseTypeTestCase = 
	{ baseTypeTests, &setupBaseTypeTestCase, "BaseType Tests", 1 };
