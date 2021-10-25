#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/*
 * El fichero tiene activado el bit setuid cuando el UID real corresponde
 * al del usuario que lo ejecuta pero el UID efectivo es el del propietario
 * del fichero.
 */

int main() {
	printf("Real UID: %d\n", getuid());
	printf("Effective UID: %d\n", geteuid());
	return 0;
}
