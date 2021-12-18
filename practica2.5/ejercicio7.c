#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int tcp6_sd, s;
	struct addrinfo hints, * res;
	ssize_t c;
	char buf[BUFFER_SIZE];

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
	
	if (connect(tcp6_sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) {
	       perror("Error connect()");
       	       return -1;
	}	       
	
	while (1) {
		scanf("%s", buf);

		if (strlen(buf) == 1 && buf[0] == 'Q') {
			break;
			/* c = send(tcp6_sd, "", 0, 1);
        		if (c == -1) {
				perror("Error send()");
				return -1;
			} */
		}
		else {
			c = send(tcp6_sd, buf, strlen(buf) + 1, 0);
        		if (c == -1) {
				perror("Error send()");
				return -1;
			} 
			c = recv(tcp6_sd, buf, BUFFER_SIZE, 0);
			buf[c] = '\0';
			printf("%s\n", buf);
		}
	}
	close(tcp6_sd);	
	return 0;
}
