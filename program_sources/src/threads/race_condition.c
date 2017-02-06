/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string.h>

int Global;
int Proceed = 0;
#define THREAD_NUM		1
#define MAX_BUF			64
#define PIPE_PATH		"/tmp/myfifo"

void *Thread1(void *x) {
	int fd;
	int readbytes = 0;
	char * myfifo = PIPE_PATH;
	char buf[MAX_BUF];

	fprintf(stdout, "Hilo arrancado\n");

	// open, read, and display the message from the FIFO
	fd = open(myfifo, O_RDONLY);

	while(readbytes <= 0)
		readbytes = read(fd, buf, MAX_BUF);
	buf[readbytes] = 0;
	printf("Received: %s\n", buf);
	close(fd);

	Global++;
	return NULL;
}

int main(int argc, char* argv[] ) {
	int i = 0;
	int fd;
	char * myfifo = PIPE_PATH;

	pthread_t t[THREAD_NUM];

	// create the FIFO (named pipe)
	mkfifo(myfifo, 0666);

	fprintf(stdout, "Run with valgrind  --tool=helgrind bin/%s\n", argv[0]);

	Global = 20;
	for (i = 0; i < THREAD_NUM; i++){
		pthread_create(&t[i], NULL, Thread1, NULL);
	}

	// write "Hi" to the FIFO
	fd = open(myfifo, O_WRONLY);

	// wait, just for fun
	sleep(1);

	// write to the pipe
	char texto[] = "Hi\n";
	write(fd, texto, strlen(texto));

	for (i = 0; i < THREAD_NUM; i++){
		pthread_join(t[i], NULL);
	}

	close(fd);
	// remove the FIFO
	unlink(myfifo);
}
