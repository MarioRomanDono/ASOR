#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h>

int main(int argc, char ** argv) {
	DIR * direct;
	struct dirent * entry;
	int size = 0;
	char path[PATH_MAX];
	int bytes;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./myls <directory>\n");
		return -1;
	}

	direct = opendir(argv[1]);
	if (direct == NULL) {
		perror("Error while opening dir");
		return -1;
	}
	
	while ((entry = readdir(direct)) != NULL) {
		printf("%s", entry->d_name);
		if (entry->d_type == DT_REG) {
			printf("\n");
			size += entry->d_reclen;
		}
		if (entry->d_type == DT_DIR) {
			printf("/\n");
		}
		if (entry->d_type == DT_LNK) {
			if ((bytes = readlink(entry->d_name, path, PATH_MAX)) == -1) {
				perror("Error while reading symlink");
				return -1;
			}
			path[bytes] = '\0';
			printf("->%s\n", path);
		}	
	
	}
	printf("Total size: %d kbytes\n", size);
	closedir(direct);
	return 0;
}
