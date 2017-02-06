/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE	0

int main(void){
	printf("Illegal writes\n");

	return EXIT_FAILURE;

	char src[5];
	sprintf(src, "Esto es una cadena muy larga");
	char dst[4];
	sprintf(dst, "Esto es una cadena larga");

	printf("%s\n", src);
	printf("%s\n", dst);

	strcpy(dst,src);
	printf("%s\n", src);

	return EXIT_SUCCESS;
}
