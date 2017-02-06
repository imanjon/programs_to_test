/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE  	1
#define FALSE	0

#define NUM_ALLOCS		10

void f(void){
	malloc(500);
}

void g(void){
	malloc(2500);

	f();
}

int main(void){
	int i;
	int* a[NUM_ALLOCS];

	for(i = 0; i < NUM_ALLOCS; i++){
		a[i] = malloc(1000);
	}

	f();

	g();

	for(i = 0; i < NUM_ALLOCS; i++){
		free(a[i]);
	}
	return EXIT_SUCCESS;
}
