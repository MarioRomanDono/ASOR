#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char ** argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: ./mydaemon <command>\n");
		return -1;
	}
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
			int fd;
			chdir("/tmp");
			if ((fd = open("/dev/null", O_RDONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
				perror("Error while opening file");
				return -1;
			}	
			if (dup2(fd, 0) == -1)  {
				perror("Error while executing dup2");
				return -1;
			}
			if ((fd = open("/tmp/daemon.out", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
				perror("Error while opening file");
				return -1;
			}	

			if (dup2(fd, 1) == -1)  {
				perror("Error while executing dup2");
				return -1;
			}
			if ((fd = open("/tmp/daemon.err", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
				perror("Error while opening file");
				return -1;
			}	
			if (dup2(fd, 2) == -1)  {
				perror("Error while executing dup2");
				return -1;
			}
			if (execvp(argv[1], argv + 1) == -1) {
				perror("Error while executing execvp");
				return -1;
			}
			break;
	}
	return 0;
}
