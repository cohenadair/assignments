// Cohen Adair, CS222-01-14W
// Header file for the Main file.

#ifndef _MAIN_
#define _MAIN_

#include <string>
using namespace std;

#include "printjob.h"

int main(int argc, char **argv);
string calculateEndTime(string startTime, string min);
int compareTimes(string timeA, string timeB);
int compareTimesRecurring(string timeA, string timeB);
void validateTimes(string &timeA, string &timeB);
void printReceive(PrintJob *j);
void printComplete(PrintJob *j, string endTime);

#endif
