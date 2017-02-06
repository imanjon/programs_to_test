/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int Global;
pthread_mutex_t mtx;// = PTHREAD_MUTEX_INITIALIZER;

void *Thread1(void *x) {
	int i;
	for (i = 0; i < 10000; i++){
		pthread_mutex_lock(&mtx);
		Global++;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

void *Thread2(void *x) {
	int i;
	for (i = 0; i < 10000; i++){
		pthread_mutex_lock(&mtx);
		Global--;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main() {
  pthread_t t[2];
//  fprintf(stderr, "Run with valgrind  --tool=helgrind bin/threads\n");
  pthread_mutex_init(&mtx, NULL);
  pthread_create(&t[0], NULL, Thread1, NULL);
  pthread_create(&t[1], NULL, Thread2, NULL);
  sleep(1);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  pthread_mutex_destroy(&mtx);
}
