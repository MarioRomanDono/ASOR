#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

static void sigchld_action(int arg) {
	while (waitpid(-1, 0, WNOHANG) != -1) {}
}

int gestionar_mensaje(int clisd, struct sockaddr_storage addr) {
	int s;
	socklen_t addrlen;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];
	size_t c;

	addrlen = sizeof(addr);
	s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	if (s != 0) {
		fprintf(stderr, "Error getnameinfo(): %s\n", gai_strerror(s));
		return -1;
	}
	printf("Hijo %d: Conexión desde %s:%s\n", getpid(), host, serv);
	
	while ((c = recv(clisd, buf, BUFFER_SIZE, 0))) {
	   	if (c == -1) {
			perror("Error recv()");
			close(clisd);
			return -1;
		}
		send(clisd, buf, c, 0);
	}
	printf("Hijo %d: Conexión terminada\n", getpid());
	return 0;
}

int main(int argc, char ** argv) {
	int tcp6_sd, s, clisd;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	struct sigaction sigchld_struct;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <direction> <port>\n", argv[0]);
		return -1;
	}
	
	sigchld_struct.sa_handler = sigchld_action;
	sigchld_struct.sa_flags = SA_RESTART;

	sigaction(SIGCHLD, &sigchld_struct, NULL);
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	s = getaddrinfo(argv[1], argv[2], &hints, &res); 
	if (s) {
		fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
	}

       	tcp6_sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (tcp6_sd == -1) {
		perror("Error socket()");
		return -1;
	}
	
	if (bind(tcp6_sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) {
	       perror("Error bind()");
       	       return -1;
	}	       
	
	freeaddrinfo(res);

	if (listen(tcp6_sd, 5)) {
	       perror("Error listen()");
       	       return -1;
	}

	while (1) {
		addrlen = sizeof(addr);
		clisd = accept(tcp6_sd, (struct sockaddr *) &addr, &addrlen);
		
		pid_t pid = fork();
		switch(pid) {
			case -1:
				perror("Error fork()");
				return -1;
			case 0:
				close(tcp6_sd);
				return gestionar_mensaje(clisd, addr);
			default:
				close(clisd);
				break;
		}
	}
	return 0;
}
