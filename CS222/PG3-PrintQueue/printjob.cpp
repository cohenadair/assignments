// Cohen Adair, CS222-01-14W
// Method file for the PrintJob class.

#include "printjob.h"

PrintJob::PrintJob(string new_time, string new_length) {
	timeOfDay = new_time;
	lengthOfJob = new_length;
}

PrintJob::PrintJob() {
	timeOfDay = "00:00";
	lengthOfJob = "0";
}

PrintJob::~PrintJob() {
	timeOfDay = "";
	lengthOfJob = "";
}

// returns the job's time of day the job was sent
string PrintJob::getTime() {
	return timeOfDay;
}

// returns how long the job will take
string PrintJob::getLength() {
	return lengthOfJob;
}


