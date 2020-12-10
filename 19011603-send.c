#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// argv[1] = want to send ps pid
// argv[2] = want to send data
// send the RTS SIGUSR1


int main(int argc, char **argv){
	union sigval sv;
	pid_t my = getpid();

	sv.sival_int = 19011603;
	sigqueue( my, SIGTSTP, sv);
}
