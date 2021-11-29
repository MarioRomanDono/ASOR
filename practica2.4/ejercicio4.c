#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	int fd;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return -1;
	}
	if ((fd = open("tuberia", O_WRONLY)) == -1) {
		perror("Error while opening pipe");
		fprintf(stderr, "Check if there is a pipe named tuberia in your directory\n");
		return -1;
	}
	if (write(fd, argv[1], strlen(argv[1]) + 1) == -1) {
		perror("Error while writing to pipe");
		return -1;
	}
	return 0;
}
