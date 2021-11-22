#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	sigset_t blk_set, rcv_set;
	char * sleep_secs = getenv("SLEEP_SECS");
	if (sleep_secs == NULL) {
		fprintf(stderr, "SLEEP_SECS not defined in env\n");
		return -1;
	}


	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);

	sigprocmask(SIG_BLOCK, &blk_set, NULL);

	sleep(atoi(sleep_secs));

	sigemptyset(&blk_set);
	sigpending(&rcv_set);

	if (sigismember(&rcv_set, SIGINT)) {
		printf("SIGINT recibida\n");
	}
	if (sigismember(&rcv_set, SIGTSTP)) {
		printf("SIGTSTP recibida\n");
		sigemptyset(&blk_set);
		sigaddset(&blk_set, SIGTSTP);
		sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
		printf("El proceso continúa despues de desbloquear SIGTSTP\n");
	}
	return 0;
}
