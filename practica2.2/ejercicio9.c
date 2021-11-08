#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(int argc, char ** argv) {
	struct stat * info;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./mystat <file>\n");
		return 0;
	}
	
        info = malloc(sizeof(struct stat));

	if ( stat(argv[1], info) == -1 ) {
		perror("Error while executing stat");
		free(info);
		return -1;
	}

	printf("Major number: %d\n", major(info->st_dev));
	printf("Minor number: %d\n", minor(info->st_dev));
	printf("Inode number: %ld\n", info->st_ino);
	printf("File type and mode: %d\n", info->st_mode);
	printf("Last time access: %s", ctime(&info->st_atime));

	free(info);
	return 0;
}
