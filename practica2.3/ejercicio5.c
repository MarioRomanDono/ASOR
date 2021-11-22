#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int main(void) {
	char path[PATH_MAX];
	pid_t pid = getpid();
	pid_t pgid = getpgid(pid);
	pid_t sid = getsid(pid);
	printf("PID: %d\n", pid);
	printf("PPID: %d\n", getppid());
	printf("SID: %d\n", sid);
	printf("PGID: %d\n", pgid);
	printf("Max number of opened files: %ld\n", sysconf(_SC_OPEN_MAX));

	if ( getcwd(path, PATH_MAX) == NULL) {
		perror("Error while executing getcwd");
		return -1;
	}
	printf("Current directory: %s\n", path);
       	return 0;
}
