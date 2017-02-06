#include <pthread.h>
#include <stdio.h>

int Global;
#define THREAD_NUM		2

void *Thread1(void *x) {
	Global++;
	return NULL;
}

int main() {
	int i = 0;

	fprintf(stdout, "Run with valgrind  --tool=helgrind bin/threads\n");
	pthread_t t[THREAD_NUM];


	for (i = 0; i < THREAD_NUM; i++){
		pthread_create(&t[i], NULL, Thread1, NULL);
	}
	for (i = 0; i < THREAD_NUM; i++){
		pthread_join(t[i], NULL);
	}
}
