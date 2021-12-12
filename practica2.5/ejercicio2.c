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
	size_t size;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];
	struct tm * t_info;
	time_t t;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <direction> <port>\n", argv[0]);
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

       	udp6_sd = socket(AF_INET6, SOCK_DGRAM, 0);
	if (udp6_sd == -1) {
		perror("Error socket()");
		return -1;
	}
	
	if (bind(udp6_sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) {
	       perror("Error bind()");
       	       return -1;
	}	       
	
	while (1) {
		addrlen = sizeof(addr);
		c = recvfrom(udp6_sd, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &addrlen);
	        if (c == -1) {
			perror("Error recvfrom()");
			return -1;
		}
		buf[c] = '\0';
		s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		if (s != 0) {
			fprintf(stderr, "Error getnameinfo(): %s\n", gai_strerror(s));
			return -1;
		}
		printf("Recibidos %ld bytes de %s:%s\n", c, host, serv);

		if (buf[0] == 'q') {
			break;
		}
		else if ( buf[0] != 't' && buf[0] != 'd') {
			fprintf(stderr, "Comando %c no soportado\n", buf[0]);
		}
		else {
			t = time(NULL);
			t_info = localtime(&t);	
			if (buf[0] == 't') {
				size = strftime(buf, BUFFER_SIZE, "%H:%M:%S", t_info);
			}
			else {
				size = strftime(buf, BUFFER_SIZE, "%Y-%m-%d", t_info);
			}
			
			c = sendto(udp6_sd, buf, size, 0, (struct sockaddr * ) &addr, addrlen);
	        	if (c == -1) {
				perror("Error sendto()");
				return -1;
			}			
		}
	}
	
	close(udp6_sd);	
	printf("Saliendo...\n");
	return 0;
}
