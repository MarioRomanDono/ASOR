#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	int p_h[2];
	int h_p[2];
	int fin = 0, n_mensajes = 0;
	char buffer[256];
	if (pipe(p_h)) {
		perror("Error while creating pipe");
		return -1;
	}
	if (pipe(h_p)) {
		perror("Error while creating pipe");
		return -1;
	}
	pid_t pid = fork();
	switch(pid) {
		case -1:
			perror("Error while executing fork");
			return -1;
		case 0:
			close(p_h[1]);
			close(h_p[0]);
			while (!fin) {
				int n = read(p_h[0], buffer, 256);
				buffer[n] = '\0';
				printf("%s\n", buffer);
				sleep(1);
				if (++n_mensajes == 10) {
					write(h_p[1], "q", 1);
					fin = 1;
				}
				else {
					write(h_p[1], "l", 1);
				}
			}
			close(p_h[0]);
			close(h_p[1]);
			break;
		default:
			close(p_h[0]);
			close(h_p[1]);
			while(!fin) {
				scanf("%s", buffer);
				write(p_h[1], buffer, strlen(buffer) + 1);
				read(h_p[0], buffer, 1);
				if (buffer[0] == 'q') {
					fin = 1;
				}
			}
			close(p_h[1]);
			close(h_p[0]);
			break;
	}
	return 0;
}
