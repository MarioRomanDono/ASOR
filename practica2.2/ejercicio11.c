#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	struct stat * info;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: ./mylink <file>\n");
		return -1;
	}

	info = malloc(sizeof(struct stat));
	
	if (stat(argv[1], info) == -1) {
		perror("Error while executing stat");
		return -1;
	}

	if (S_ISREG(info->st_mode)) {
		if (link(argv[1], "hard_link") == -1) {
			perror("Error while executing link");
			free(info);
			return -1;
		}
		if (symlink(argv[1], "sys_link") == -1) {
			perror("Error while executing syslink");
			free(info);
			return -1;
		}
	}

	free(info);
	return 0;
}
