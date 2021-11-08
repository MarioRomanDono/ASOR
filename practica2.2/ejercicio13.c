#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
	int fd;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./mydup <file>\n");
		return -1;
	}
	
	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
		perror("Error while opening file");
		return -1;
	}

	if (dup2(fd, 1) == -1)  {
		perror("Error while executing dup2");
		return -1;
	}
	if (dup2(fd, 2) == -1)  {
		perror("Error while executing dup2");
		return -1;
	}
	
	printf("Esto es una prueba de que la salida estándar se redirige\n");
	fprintf(stderr, "Ahora se redirige la salida de error\n");
	close(fd);
	return 0;
}
