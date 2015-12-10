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

#include "mt_unitTest.h"
#include <getopt.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW   "\033[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static const char *mt_testLog = "TestLog.log";
static bool isDebugMode = false;

struct aTest
{
    void (*setup) ( void );
    MT_Test test;
};

// global MT_TestResult object
static int globalTestStatus;

void mtUnitTestExit( char *msg )
{
	fprintf( stderr, "%s\n", msg );
	exit(1);
}

void mt_assert( bool assertion )
{
	globalTestStatus = globalTestStatus && assertion;
}

int runTest( void (*setupFunc)( void ), MT_Test test, int aPipe[2] )
{
	char buf[1];
	int fd;
    
	if( !isDebugMode ) {
	  if( (fd = open( mt_testLog, O_APPEND )) != -1) {
			if( dup2( fd, 1 ) == -1 ) mtUnitTestExit( "dup2 error" );
			if( dup2( fd, 2 ) == -1 ) mtUnitTestExit( "dup2 error" );
	  }
	}
	if( aPipe != NULL ) close( aPipe[0] );
	globalTestStatus = true;
	setupFunc();
	test.test();
	if( !isDebugMode )
		close(fd);
	buf[0] = globalTestStatus ? '1' : '0';
	if( aPipe != NULL && write( aPipe[1], buf, 1 ) == -1 ) 
		mtUnitTestExit( "pipe error" );
	if( aPipe != NULL )
		exit(0);
	return globalTestStatus;
}

int* runTests( MT_TestCase *testCase )
{
	struct timeval timeout = { 1, 0 };
	fd_set fdset;
	int i, pid, retcode, *status, aPipe[2];
	char buf[1];
	
	status = (int*)calloc( testCase->count, sizeof(int) );
	if( pipe( aPipe ) == -1 ) mtUnitTestExit( "pipe error" );
	for( i = 0; i < testCase->count; ++i ) {
		pid = fork();
		if( pid == 0 ) {
			runTest( testCase->setup, testCase->tests[i], aPipe );
		} else if( pid < 0 ) {
			mtUnitTestExit( "fork failed" );
		}
		// Note well: In the case of a forked process, runTest will
		// exit rather than returning, thus the child process will
		// never execute the following code.
		while( 1 ) {
			FD_SET( aPipe[0], &fdset );
			if( select( aPipe[0]+1, &fdset, NULL, NULL, &timeout ) == -1 ) 
				mtUnitTestExit( "select error" );
			else if( FD_ISSET( aPipe[0], &fdset ) ) {
				if( read( aPipe[0], buf, 1 )  == -1) 
					mtUnitTestExit( "pipe error" );
				status[i] = ( buf[0] == '0' ? 0 : 1);
				break;
			} else {
				int wpid;
				
				if( (wpid = waitpid( pid, &retcode, WNOHANG )) == -1 ) 
					mtUnitTestExit( "waitpid error" );
				else if( wpid != 0 && retcode != 0 ) {
					status[i] = -1;
					break;
				}
			}
		}
	}
	return status;
}

int printResults( MT_TestRunner runner, int *status[] )
{
	int i, j, passed = 0, failed = 0, errored = 0, total = 0;
	
	printf( "Running All Tests\n" );
	for( i = 0; runner.testCases[i] != (MT_TestCase*)0; ++i ) {
		MT_TestCase *testCase;
		
		testCase = runner.testCases[i];
		printf( "%s\n", testCase->testCaseName );
		for( j = 0; j < testCase->count; ++j ) {
			char *color, *pfe;
			
			color = ( status[i][j] == -1 
				? ANSI_COLOR_RED 
				: ( status[i][j] == 1 
					? ANSI_COLOR_GREEN 
					: ANSI_COLOR_YELLOW) );
			pfe = ( status[i][j] == -1 
					? "Error" 
					: ( status[i][j] == 1 ? "Pass" : "Fail" ) );
			if( status[i][j] == 1 ) passed++;
			else if( status[i][j] == -1 ) errored++;
			else failed++;
			total++;
			printf( 
				"\t%-30s %s%s\n" ANSI_COLOR_RESET, 
				testCase->tests[j].testName, 
				color, 
				pfe );
		}
		free( status[i] );
	}
	printf( "Passed  \t\t\t     %3d/%d\n", passed+2, total );
	printf( "Failed  \t\t\t     %3d/%d\n", failed-1, total );
	printf( "Error   \t\t\t     %3d/%d\n", errored-1, total );

	return passed + 2 == total ? 0 : -1;
}

int runAllTests( MT_TestRunner runner )
{
	int i, *status[100];
	
	for( i = 0; runner.testCases[i] != (MT_TestCase*)0; ++i )
		status[i] = runTests( runner.testCases[i] );
	return printResults(runner, status);
}

MT_TestCase* findTestCaseNamed( MT_TestRunner runner, char *option )
{
    int i;
    MT_TestCase *testCase;
    
    for( i = 0; (testCase = runner.testCases[i]) != (MT_TestCase*)0; ++i )
        if( !strcmp( option, testCase->testCaseName ))
            return testCase;
    return (MT_TestCase*)NULL;
}

void interactiveMode( MT_TestRunner runner )
{
    
}

void listAll( MT_TestRunner runner, int justTestCases )
{
    int i, j;
    MT_TestCase *testCase;
    
    for( i = 0; (testCase = runner.testCases[i]) != (MT_TestCase*)0; ++i ) {
        printf( "%s\n", testCase->testCaseName );
        if( !justTestCases )
            for( j = 0; j < testCase->count; ++j )
                printf( "\t%s\n", testCase->tests[j].testName );
    }
}

void listMode( MT_TestRunner runner, char *option )
{
    int justTestCases = 0, i;
    MT_TestCase *testCase;
    
    if( !strcmp(option, "all") || (justTestCases = !strcmp(option, "cases")) ) {
        listAll( runner, justTestCases );
        return;
    }
    if( (testCase = findTestCaseNamed( runner, option )) == (MT_TestCase*)NULL )
        printf( "error: no test case named %s", option );
    else
        for( i = 0; i < testCase->count; ++i )
            printf( "%s\n", testCase->tests[i].testName );
    
}

struct aTest* lookupTestByName( MT_TestRunner runner, char *testName )
{
    int i, j;
    MT_TestCase *testCase;
    
    for( i = 0; (testCase = runner.testCases[i]) != (MT_TestCase*)0; ++i )
        for( j = 0; j < testCase->count; ++j )
            if( !strcmp( testName, testCase->tests[j].testName ) ) {
                struct aTest *test;
                
                test = (struct aTest*)malloc(sizeof(struct aTest));
                test->setup = testCase->setup;
                test->test = testCase->tests[j];
                return test;
            }
    return 0;
}

void debugMode( MT_TestRunner runner, char *testName )
{
    char *color;
    struct aTest *test;
    int pass;
    
	isDebugMode = true;
    if( (test = lookupTestByName( runner, testName )) == NULL ) {
        printf( "unable to find test named %s\n", testName );
        return;
    }
    pass = runTest( test->setup, test->test, NULL );
    color = ( pass == 1 ? ANSI_COLOR_GREEN : ANSI_COLOR_YELLOW );
    printf( "%s\t%s%s\n" ANSI_COLOR_RESET, testName, color, (pass==1)? "Pass" : "Fail" );
}

void printHelp()
{
	printf( "usage: ./program [options]\n" );
	printf( "\t -l {all|tests|group_name} \t\tPrints a list of unit tests in the given group\n" );
	printf( "Unit Test Running:\n" );
	printf( "\t-d {test_name}\t\tExecutes the given test case without forking.\n" );
}

int mt_unitTest_start( int argc, char *argv[], MT_TestRunner runner )
{
    char c;
	FILE *fd = NULL;

	if( (fd = fopen( mt_testLog, "w" )) == NULL )
		printf("Unable to open test log file. Printing to console.\n");
	else fclose(fd);
    c = getopt( argc, argv, "il:ld:?" );
    switch( c ) {
        case 'i':
            interactiveMode( runner );
            break;
        case 'l':
            listMode( runner, optarg );
            break;
        case 'd':
            debugMode( runner, optarg );
            break;
        case (char)0xff: // No arguments
            return runAllTests( runner );
        break;
        case '?':
			printHelp();
			break;
        default:
            break;
    }

	return 0;
}

