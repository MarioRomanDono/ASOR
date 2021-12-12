#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	struct addrinfo * res, * rp;
	int s;
	char host[BUFFER_SIZE];
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <direction>\n", argv[0]);
		return -1;
	}

	s = getaddrinfo(argv[1], NULL, NULL, &res);
       	if (s != 0) {
		fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
	}

	for (rp = res; rp != NULL; rp = rp->ai_next) {
		s = getnameinfo(rp->ai_addr, rp->ai_addrlen, host, BUFFER_SIZE, NULL, 0, NI_NUMERICHOST);
		if (s != 0) {
			fprintf(stderr, "Error getnameinfo(): %s\n", gai_strerror(s));
			return -1;
		}
		printf("%s\t%d\t%d\n", host, rp->ai_family, rp->ai_socktype);
	}
	return 0;
}
