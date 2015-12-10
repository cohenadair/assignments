// MIT License
//
// Copyright (c) The contributors, Josh Fridstrom, Steve Jarvis,
// Kurt Kilpela, Brian Krent, and John Sarkela who have collectively contributed
// elements to this software ("The Modtalk Group"), 2013 All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef MT_UNITTEST
#define MT_UNITTEST

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

typedef struct mt_test {
	void (*test) ( void );
	char *testName;
}MT_Test;

typedef struct mt_testcase {
	MT_Test *tests;
	void (*setup) ( void );
	char *testCaseName;
	int count;
}MT_TestCase;

typedef struct mt_testrunner {
	MT_TestCase **testCases;
}MT_TestRunner;

int mt_unitTest_start( int argc, char *argv[], MT_TestRunner runner );
int runAllTests( MT_TestRunner runner );
void mt_assert( bool assertion );

#endif

