// Cohen Adair, CS222-01-14W
// This program will read in print jobs from a text file "pg3cmds.txt" and print
// the start time and end time of each job.

#include <iostream>
#include <fstream>
#include <string>
#include "main.h"
#include "queue.h"
using namespace std;

int main(int argc, char **argv) {
	
	ifstream in ("pg3cmds.txt");
	Queue *q = new Queue();
	Queue *qWaiting = new Queue();
	string tmpTime, tmpPrint, tmpMin;
	string endTime = "12:59";
	PrintJob *j = NULL, *curr = NULL;
	bool dequeue = true;
	
	// add each print command to the queue
	while (true) {
		in >> tmpTime >> tmpPrint >> tmpMin;
		
		if (in.eof()) // why is an extra node added if I use while (!in.eof()) rather than this break?
			break;
		
		q->ENQUEUE(new PrintJob(tmpTime, tmpMin));
	}

	// first command
	if (!q->ISEMPTY()) {
		curr = q->DEQUEUE();
		endTime = calculateEndTime(curr->getTime(), curr->getLength());
		printReceive(curr);
	}

	while (true) {
		if (!q->ISEMPTY()) {
			if (dequeue)
				j = q->DEQUEUE();

			if (compareTimes(j->getTime(), endTime) < 0) {
				printReceive(j);
				qWaiting->ENQUEUE(j);
				dequeue = true;
				continue;
			} else {
				printComplete(curr, endTime);
				dequeue = false; // going to need this to keep j for next iteration of the loop
			}

			if (qWaiting->ISEMPTY()) {
				printReceive(j);
				qWaiting->ENQUEUE(j);
				dequeue = true;
			}
		}

		if (!qWaiting->ISEMPTY()) {
			if (q->ISEMPTY())
				printComplete(curr, endTime);

			curr = qWaiting->DEQUEUE();

			if (compareTimes(endTime, curr->getTime()) < 0)
				endTime = calculateEndTime(curr->getTime(), curr->getLength());
			else 
				endTime = calculateEndTime(endTime, curr->getLength());

			if (q->ISEMPTY())
				printComplete(curr, endTime);
		} else
			break;
	}

	in.close ();

	system("pause");
	return 0;
}

// adds "min" to "startTime"; returns the new time
string calculateEndTime(string startTime, string min) {
	string res = startTime;
	while (res.length() != 5)
		res = "0" + res;

	int l = res.length();
	int minutes = stoi(min);

	// add 1 minute "min" times
	for (int i = 1; i <= minutes; i++) 
		if (res[l - 1] < '9') // 00:00 to 00:09
			res[l - 1] += 1;
		else if (res[l - 2] < '5') { // 00:10 to 00:59
			res[l - 2] += 1;
			res[l - 1] = '0';
		} else if (res[l - 5] == '0' && res[l - 4] < '9') { // 01:00 to 09:59
			res[l - 4] += 1;
			res[l - 2] = res[l - 1] = '0';
		} else if (res[l - 5] == '0' && res[l - 4] == '9') { // 10:00
			res[l - 4] = res[l - 2] = res[l - 1] = '0';
			res[l - 5] = '1';
		} else if (res[l - 4] < '2') { // 10:01 to 12:59
			res[l - 4] += 1;
			res[l - 2] = res[l - 1] = '0';
		} else if (res == "12:59")
			res = "1:00";

	// remove leading 0
	if (res[0] == '0')
		res = res.substr(1);

	return res;
}

// returns:
//   -1 if timeA < timeB
//    0 if timeA == timeB
//    1 if timeA > timeB
int compareTimes(string timeA, string timeB) {
	// adds a preceeding 0 to the times if needed
	while (timeA.length() != 5)
		timeA = "0" + timeA;

  	while (timeB.length() != 5)
  		timeB = "0" + timeB;

	return compareTimesRecurring(timeA, timeB);
}

// compares timeA and timeB using recursion 
int compareTimesRecurring(string timeA, string timeB) {
	if (timeA.length() == 0)
		return 0;

	// compares each digit of the time, starting with the first
	if (timeA[0] == timeB[0]) {
		return compareTimesRecurring(timeA.substr(1), timeB.substr(1));
	} else if (timeA[0] < timeB[0])
		return -1;
	else if (timeA[0] > timeB[0])
		return 1;

	return NULL;
}

// prints the job received message
void printReceive(PrintJob *j) {
	cout << j->getTime() << " received " << j->getLength() << "-minute print request." << endl;
}

// prints the job complete message
void printComplete(PrintJob *j, string endTime) {
	cout << endTime << " completed print request submitted at " << j->getTime() << "." << endl;
}
