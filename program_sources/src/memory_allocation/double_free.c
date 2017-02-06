#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE	0

int main(void){
	printf("Double frees\n");

	char* foo = malloc(127);
	free(foo);
	free(foo);

	return EXIT_SUCCESS;
}
