#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*signal handler*/
/*Or not Unix singal*/
void sighandler(int signo, siginfo_t *si, void *tmp){
	
		printf("User RTS signal %d\n", si->si_pid);
		printf("Sig Number %d\n", si->si_signo);
		printf("My student id is %d\n", si->si_value.sival_int);
}

int main(){
	struct sigaction si;
	printf("My pid %d\n", getpid());

	//sa_flags = SA_SIGINFO
	//enter the signal handler
	sigemptyset(&si.sa_mask);
	si.sa_flags = SA_SIGINFO;
	si.sa_restorer = NULL;
	si.sa_sigaction = sighandler;
	
	//intsall RTS signalhandler
	if(sigaction(SIGTSTP, &si, 0) == 1){
		printf("sinal error\n");
		exit(0);
	}
	while(1) sleep(1);
}

