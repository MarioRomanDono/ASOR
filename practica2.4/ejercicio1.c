#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char ** argv) {
	int fd[2];
	if (argc != 5) {
		fprintf(stderr, "Usage: %s <command1> <arg1> <command2> <arg2>\n", argv[0]);
		return -1;
	}	
	if (pipe(fd)) {
		perror("Error while creating pipe");
		return -1;
	}
	pid_t pid = fork();
	switch(pid) {
		case -1:
			perror("Error while executing fork");
			return -1;
		case 0:
			close(0);
			if (dup2(fd[0], 0) == -1)  {
				perror("Error while executing dup2");
				return -1;
			}
			close(fd[0]);
			close(fd[1]);
			if (execlp(argv[3], argv[3], argv[4], NULL)) {
				perror("Error while executing execvp");
				return -1;
			}
			break;
		default:
			close(1);
			if (dup2(fd[1], 1) == -1)  {
				perror("Error while executing dup2");
				return -1;
			}
			close(fd[0]);
			close(fd[1]);
			if (execlp(argv[1], argv[1], argv[2], NULL)) {
				perror("Error while executing execvp");
				return -1;
			}
			wait(NULL);
			break;
	}
	return 0;
}
