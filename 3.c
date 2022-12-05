#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int a = 0;

static void signal_handler(int signo) {
	if (signo == SIGUSR1){
		printf("%d. SIGUSR1 signal caught!\n", a);
		a++;
	}
}

int main(void) {
	int flag = 0;
	pid_t pid;	
	pid = fork();
	while(1){
		if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
			fprintf(stderr, "SIGUSeR1 can't process!\n");
			exit(EXIT_FAILURE);
		}	
		if (pid == 0) {
			kill(getppid(), SIGUSR1);
			pause();
			printf("Childs process:\n");
		} 
		if (pid > 0) {
			pause();
			printf("Parent process:\n");
			kill(pid, SIGUSR1);
		} 
		//sleep(1);
	}
	return 0;
}

