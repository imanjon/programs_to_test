/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE	1
#define FALSE	0

#undef BUCLE
#define COUNT	5

// Macro definitions
#define SUMA(a, b)  (a) + (b) //a#b
#define RESTA(x, y)  (x) - (y) //x##y


#define SUMA(a, b)  (a) + (b) //a#b
#define CONCATENA(x, y) x##y
#define PRINT_TOKEN(token) printf(#token " is %d\n", token)

int main(void){
	int a = 3;
	int b = 4;

	printf("Foo\n");

	assert(TRUE);

	printf("%d\n", SUMA(a, b));
	printf("%d\n", RESTA(a, b));

	printf("%d\n", CONCATENA(234, 123));

#ifndef S_SPLINT_S
	const char texto_en_lineas[] = "hola"
			", "
			"mundo!\n";
	printf("%s", texto_en_lineas);
	printf("%s", CONCATENA(texto, _en_lineas));
#endif

	PRINT_TOKEN(4 * 5);

#ifdef BUCLE
	int i;
	for (;;) {
	}
	i = COUNT;
	while ((--i) > 0);
#endif

	printf("Final del programa\n");
	return EXIT_SUCCESS;
}
