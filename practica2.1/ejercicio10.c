#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>

int main() {
	struct passwd * passwd_info;
	
	printf("Real UID: %d\n", getuid());
	printf("Effective UID: %d\n", geteuid());

	passwd_info = getpwuid(getuid());
	printf("Username: %s\n", passwd_info->pw_name);
	printf("Home directory: %s\n", passwd_info->pw_dir);
	printf("User description: %s\n", passwd_info->pw_gecos);
	
	return 0;
}
