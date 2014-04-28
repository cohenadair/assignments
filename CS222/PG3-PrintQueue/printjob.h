// Cohen Adair, CS222-01-14W
// Header file for the PrintJob class.

#ifndef _PRINTJOB_
#define _PRINTJOB_

#include <string>
using namespace std;

class PrintJob {

private:
	string timeOfDay;
	string lengthOfJob;
	string endTime;

public:
	PrintJob(string newTime, string newLength);
	PrintJob();
	~PrintJob();
	string getTime();
	string getLength();

};

#endif
