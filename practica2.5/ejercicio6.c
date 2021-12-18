#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int tcp6_sd, s, clisd;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	ssize_t c;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <direction> <port>\n", argv[0]);
		return -1;
	}

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
	if (listen(tcp6_sd, 5)) {
	       perror("Error listen()");
       	       return -1;
	}       
	
	addrlen = sizeof(addr);
	clisd = accept(tcp6_sd, (struct sockaddr *) &addr, &addrlen);
	
	s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	if (s != 0) {
		fprintf(stderr, "Error getnameinfo(): %s\n", gai_strerror(s));
		close(clisd);
		return -1;
	}
	printf("Conexión desde %s:%s\n", host, serv);
	while ((c = recv(clisd, buf, BUFFER_SIZE, 0))) {
	       	if (c == -1) {
			perror("Error recv()");
			close(clisd);
			return -1;
		}
		send(clisd, buf, c, 0);
	}	
	
	close(clisd);
	printf("Conexión terminada\n");	
	
	return 0;
}
