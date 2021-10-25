#include <sys/types.h>
#include <unistd.h>

int main() {
	setuid(0);
	return 1;
}
