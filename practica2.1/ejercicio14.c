#include <time.h>
#include <stdio.h>

int main() {
	struct tm * time_info;
	time_t t = time(NULL);

	time_info = localtime(&t);

	printf("Year: %d\n", 1900 + time_info->tm_year);

	return 0;
}
