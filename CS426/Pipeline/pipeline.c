#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// This signal handling code is a snippet that I reuse whenever
// I write programs that fork lots of processes. It is my stock 
// example of setting a signal handler (the modern way) and 
// handling the death of child processes.

// sigchld_handler(int s)
//	mourn dead children by waiting
//		we don't actually care which child,
//		and as we are impatient, we do not 
//		wish to wait if there are no children
void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// setDeadChildHandler()
//	set a handler for the SIGCHLD interrupt
//	that mourns dead children
void setDeadChildHandler(){
	struct sigaction sigact;

	sigact.sa_handler = sigchld_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	if( sigaction(SIGCHLD, &sigact, NULL) == -1){
		fprintf(stderr, "Could not set SIGCHLD handler.\n");
		exit(-1);
	}
}

// exec takes as one of it's arguments,
// an argv vector which represents the command 
// it is the argv that the corresponding main() will see.
// we will use execvp() this version looks for the 
// executable based upon the value of the PATH env variable
char *lsCmd[] = { "ls", "-l", NULL };
char *psCmd[] = { "ps", "aux", NULL };
char *grepCmd[] = { "grep", "cohen", NULL };

// forkCommand(argv)
//	fork a child process
//		on fork error return -1
//	child:
//		execs command in argv
//			on exec error exit 1
//	parent:
//		return child pid

pid_t forkCommand( char *argv[] ){
	int pid = fork();

	if (pid == -1)
		return -1;

	// child
	if (pid == 0) {
		execvp(argv[0], argv);
		exit(1);
	}

	return pid;
}

// forkCommandRedirect(char *argv[], int fds[])
//	fork a child process
//		on fork error return -1
//	child:
//		redirect fds
//			on redirect error exit 1
//		execs command in argv
//			on exec error exit 1
//	parent:
//		return child pid

// note on redirects:
//	stdin == 0; stdout == 1; stderr == 2;
//	fds[] is a three element array
//  if fds[i] is -1, then no redirect is required.
//	otherwise, fds[i] should be redirected to i using dup2
pid_t forkCommandRedirect( char *argv[], int fds[] ){
	int pid = fork();

	if (pid == -1)
		return -1;

	// child
	if (pid == 0) {
		for (int i = 0; i < 2; i ++)
			if (fds[i] > 0) {
				if (dup2(fds[i], i) == -1)
					exit(1);
				close(fds[i]);
			}

		execvp(argv[0], argv);
		exit(1);
	}

	return pid;
}

// samplePipeline()
//	set a signal handler for SIGCHLD
//	set up the arrays that indicate how redirects should be done
//	close the pipeline fds after the forks

void samplePipeline(){
	pid_t	cmdPid, deadPid;
	int		pipeFds[2];
	int		proc1Fds[3] = {-1, -1, -1};
	int		proc2Fds[3] = {-1, -1, -1};

	setDeadChildHandler();
	if( pipe(pipeFds) < 0 ){
		fprintf( stderr, "Pipe error\n" );
		exit(1);
	} 
	proc1Fds[1] = pipeFds[1];
	proc2Fds[0] = pipeFds[0];
	cmdPid = forkCommandRedirect( psCmd, proc1Fds );
	cmdPid = forkCommandRedirect( grepCmd, proc2Fds );
	close(pipeFds[0]);
	close(pipeFds[1]);
}

// main()
//	If there are arguments to the program, treat them as a command line.
//	By grabbing the address of the second command line argument, we get
//	an argv array for the command line for free. (kind of a hack)
//
//  Try commands like:
//		./pipeline ls -l
//		./pipeline uname -a
//		./pipeline who am i
//
//	Otherwise, build a sample pipeline that redirects the output of "ps aux" 
//	into "grep root"
//
//	Try changing the command to grep for your user name and see if that works.

int main(int argc, char *argv[]){
	if( argc > 1 ){
		int status;
		if( forkCommand( &argv[1] ) > 0 )
			wait(&status);
	} else {
		samplePipeline();
	}
	return 0;
}