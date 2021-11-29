#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	int fd1, fd2, max_fd, cambios, bytes;
	char buffer[256];
	fd_set set;

	fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
	fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
	FD_ZERO(&set);
	FD_SET(fd1, &set);
	FD_SET(fd2, &set);
	max_fd = (fd1 > fd2) ? fd1 : fd2;

	cambios = select(max_fd + 1, &set, NULL, NULL, NULL);

	if (cambios == -1) {
		perror("select()");
		return -1;
	}
	else if (cambios) {
		if (FD_ISSET(fd1, &set)) {
			bytes = read(fd1, buffer, 256);
			buffer[bytes] = '\0';
			close(fd1);
			fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
			printf("Se ha escrito en tuberia1. Datos: %s", buffer);
		}
		else {
			bytes = read(fd2, buffer, 256);
			buffer[bytes] = '\0';
			close(fd2);
			fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
			printf("Se ha escrito en tuberia2. Datos: %s", buffer);
		}
	}
	else {
		printf("Ningun dato nuevo\n");
	}
	return 0;
}
