#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo) {
	if (signo == SIGINT)
		printf("SIGINT signal caught!\n");
	else if (signo == SIGTERM)
		printf("SIGTERM signal caught!\n");
	else {
		fprintf(stderr, "Unexpected signal!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


int main (void) {
	struct sigaction sa;
	//sigset_t newset;
    sa.sa_handler = signal_handler;
     	
	
	if (sigaction(SIGINT, &sa, 0) != 0) {
		fprintf(stderr, "Can't process SIGINT!\n");
		exit(EXIT_FAILURE);
	}

	if (sigaction(SIGTERM, &sa, 0) != 0) {
		fprintf(stderr, "Can't process SIGTERM!\n");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGPROF, &sa, 0) != 0) {
		fprintf(stderr, "Can't reset SIGPROF!\n");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGHUP, &sa, 0) != 0) {
		fprintf(stderr, "Can't ignore SlGHUP!\n");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		raise(SIGTERM);
		pause();
	}
	return 0;
}
