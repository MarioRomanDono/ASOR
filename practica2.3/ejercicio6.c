#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int main(void) {
	pid_t pid = fork();
	switch(pid) {
		case -1:
			perror("Error while executing fork");
			return -1;
		case 0:
			break;
		default:
			if (setsid() == -1) {
				perror("Error while executing setsid");
				return -1;
			}
			chdir("/tmp");
			char path[PATH_MAX];
			pid_t pid = getpid();
			pid_t pgid = getpgid(pid);
			pid_t sid = getsid(pid);
			printf("PID: %d\n", pid);
			printf("PPID: %d\n", getppid());
			printf("SID: %d\n", sid);
			printf("PGID: %d\n", pgid);
			if ( getcwd(path, PATH_MAX) == NULL) {
				perror("Error while executing getcwd");
				return -1;
			}
			printf("Current directory: %s\n", path);
			break;
	}
	return 0;
}
