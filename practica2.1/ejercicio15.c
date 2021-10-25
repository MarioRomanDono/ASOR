#include <time.h>
#include <stdio.h>
#include <locale.h>

int main() {
	struct tm * time_info;
	time_t t = time(NULL);
	char buf[100];

	time_info = localtime(&t);
	
	setlocale(LC_ALL, "");

	strftime(buf, 100, "%A, %e de %B de %Y, %R", time_info);

	printf("%s\n", buf);

	return 0;
}
