#include <unistd.h>
#include <stdio.h>

int main() {
	int value;
	
	// Número máximo de enlaces
	if ((value = pathconf("ejercicio7.c", _PC_LINK_MAX)) != -1) {
		printf("Maximum number of links: %d\n", value);
	}
	else {
		perror("Error while executing pathconf");
		return -1;
	}
	// Tamaño máximo de ruta
	if ((value = pathconf("ejercicio7.c", _PC_PATH_MAX)) != -1) {
		printf("Maximum path size: %d\n", value);
	}
	else {
		perror("Error while executing pathconf");
		return -1;
	}
	// Tamaño máximo de nombre
	if ((value = pathconf("ejercicio7.c", _PC_NAME_MAX)) != -1) {
		printf("Maximum name size: %d\n", value);
	}
	else {
		perror("Error while executing pathconf");
		return -1;
	}
	return 0;
}
