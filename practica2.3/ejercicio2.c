#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(void) {
	struct sched_param param;
	int policy;

	if ( (policy = sched_getscheduler(0)) == -1) {
		perror("Error while executing sched_getscheduler");
		return -1;
	}
	
	if (policy == 0) {
		printf("Scheduler policy of current process: SCHED_OTHER\n");
	}
	else if (policy == 1) {		
		printf("Scheduler policy of current process: SCHED_FIFO\n");
	}
	else {		
		printf("Scheduler policy of current process: SCHED_RR\n");
	}

	if ( sched_getparam(0, &param) ) {
		perror("Error while executing sched_getscheduler");
		return -1;
	}
	printf("Scheduler priority of current process: %d\n", param.sched_priority);
	printf("\n");
	printf("Max priority of scheduler: %d\n", sched_get_priority_max(policy) );
	printf("Min priority of scheduler: %d\n", sched_get_priority_min(policy) );
	return 0;
}
