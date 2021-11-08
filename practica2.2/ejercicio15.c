#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	int fd;
	if (argc != 2) {
		fprintf(stderr, "Usage: ./mylock <file>\n");
		return -1;
	}
	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
		perror("Error while opening file");
		return -1;
	}
	
	if ( lockf(fd,F_TLOCK, 0) == -1) {
		printf("Blocked file\n");
	}
	else {
		printf("Time: %ld\n", time(NULL));
		sleep(30);
		lockf(fd, F_ULOCK, 0);
		printf("Time: %ld\n", time(NULL));
	}

	close(fd);
	return 0;
}
