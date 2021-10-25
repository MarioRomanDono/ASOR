#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	struct utsname * sysinfo = malloc(sizeof(struct utsname));

	if (uname(sysinfo) == 0) {
		printf("Operating system name: %s\n", sysinfo->sysname);
		printf("Nodename: %s\n", sysinfo->nodename);
		printf("Operating system release: %s\n", sysinfo->release);
		printf("Operating system version: %s\n", sysinfo->version);
		printf("Hardware identifier: %s\n", sysinfo->machine);
	}
	else {
		perror("Error while executing uname");
		return -1;
	}
	return 0;
}
