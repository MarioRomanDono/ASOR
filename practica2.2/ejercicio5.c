#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	int fd = open("prueba", O_RDWR | O_CREAT, 0645);
	if (fd == -1) return -1;
	close(fd);
	return 0;
}
