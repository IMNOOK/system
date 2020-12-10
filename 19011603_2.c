#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int t = 0;

void handler(int signo){
	if( signo == SIGINT){
		printf("Receive signal: %d\n",signo);
		t = 0;
	}else{
		printf("Waiting for signal to be received! Count: %d\n",t);
		t++;
	}
	
	alarm(1);
}

int main(void){
	struct sigaction act;

	sigemptyset(&act.sa_mask); //&act.sa_mask should be empty
	sigaddset(&act.sa_mask, SIGQUIT); //Only SIGQUIT should be added
	sigaddset(&act.sa_mask, SIGALRM); //and alrm
	act.sa_flags = 0;
	act.sa_handler = handler;

	if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0){
		perror("sigaction error\n");
		exit(1);
	}

	if(sigaction(SIGALRM, &act,(struct sigaction *)NULL) < 0)
		perror("can't catch sigalrm");

	handler(1);
	alarm(1);
	for(;;)
		pause();

	exit(EXIT_SUCCESS);
}
