#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int udp6_sd, s;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	ssize_t c;
	char buf[BUFFER_SIZE];

	if (argc != 4) {
		fprintf(stderr, "Usage: %s <direction> <port> <command>\n", argv[0]);
		return -1;
	}

	if (argv[3][0] != 't' && argv[3][0] != 'd' && argv[3][0] != 'q') {
		fprintf(stderr, "Comando %s no soportado\n", argv[3]);
		return -1;
	}


	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	s = getaddrinfo(argv[1], argv[2], &hints, &res); 
	if (s) {
		fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
	}

       	udp6_sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (udp6_sd == -1) {
		perror("Error socket()");
		return -1;
	}
	
	if (connect(udp6_sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) {
	       perror("Error connect()");
       	       return -1;
	}	       
	
	addrlen = sizeof(addr);
	c = sendto(udp6_sd, argv[3], strlen(argv[3]) + 1, 0, (struct sockaddr * ) res->ai_addr, res->ai_addrlen);
        if (c == -1) {
		perror("Error sendto()");
		return -1;
	}
	if (argv[3][0] != 'q') { // Si se ha enviado q no hay que esperar respuesta, en caso contrario sí
		c = recvfrom(udp6_sd, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &addrlen);
       		if (c == -1) {
			perror("Error recvfrom()");
			return -1;
		}
		buf[c] = '\0';

		printf("%s\n", buf);
	}

	close(udp6_sd);	
	printf("Saliendo...\n");
	return 0;
}
